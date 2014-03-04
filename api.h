#ifndef _LIBMATTING_API_H_
#define _LIBMATTING_API_H_

#include <boost/scoped_array.hpp>
#include <cstdint>
#include <string.h>

#include "utils.h"

// Contains the current state of the matting
class MattingState {
 public:
  // The image is given in the lab colorspace. Each of lab_l, lab_a, lab_b is
  // a W*H array stored in row-major order
  // MattingState makes an internal copy of the image
  MattingState(uint8_t* lab_l, uint8_t* lab_a, uint8_t* lab_b, int W, int H);
  ~MattingState();

  // Note that do not store all scribbles as a simple boolean mask because of
  // the way user interaction is handled (see Bai09). Basically, scribbles
  // ordering is important to let user do local corrections that do not influence
  // the whole image. In other words, doing the matting with the same set of
  // scribbles but in different order might result in different result.
  void AddScribble(const Scribble& s);

  // Fill mask with the foreground mask resulting from the matting.
  // 255 indicates foreground pixels, 0 background.
  void GetForeground(uint8_t* mask);

 private:
  int W, H;
  boost::scoped_array<uint8_t> lab_l, lab_a, lab_b;
  boost::scoped_array<double> fg_pdf, bg_pdf;
  boost::scoped_array<double> fg_likelihood, bg_likelihood;
  boost::scoped_array<double> fg_dist, bg_dist;
  boost::scoped_array<uint8_t> final_mask;

  uint8_t* channels[3];

  std::vector<Scribble> scribbles;
};

#endif
