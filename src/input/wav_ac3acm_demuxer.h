/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL v2
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   WAV AC-3 (ACM mode) demuxer module

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#ifndef MTX_INPUT_WAV_AC3ACM_DEMUXER_H
#define MTX_INPUT_WAV_AC3ACM_DEMUXER_H

#include "common/common_pch.h"

#define AC3ACM_READ_SIZE 100000

class wav_ac3acm_demuxer_c: public wav_demuxer_c {
protected:
  ac3::frame_c m_ac3header;
  memory_cptr m_buf[2];
  int m_cur_buf;
  bool m_swap_bytes;

public:
  wav_ac3acm_demuxer_c(wav_reader_c *reader, wave_header *wheader);

  virtual ~wav_ac3acm_demuxer_c();

  virtual bool probe(mm_io_cptr &io);

  virtual int64_t get_preferred_input_size() {
    return AC3ACM_READ_SIZE;
  };

  virtual unsigned char *get_buffer() {
    return m_buf[m_cur_buf]->get_buffer();
  };

  virtual void process(int64_t len);
  virtual generic_packetizer_c *create_packetizer();

  virtual unsigned int get_channels() const;
  virtual unsigned int get_sampling_frequency() const;
  virtual unsigned int get_bits_per_sample() const;

protected:
  virtual int decode_buffer(int len);
};

#endif  // MTX_INPUT_WAV_AC3ACM_DEMUXER_H
