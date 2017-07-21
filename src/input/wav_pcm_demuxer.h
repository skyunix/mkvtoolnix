/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL v2
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   WAV PCM demuxer module

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#ifndef MTX_INPUT_WAV_PCM_DEMUXER_H
#define MTX_INPUT_WAV_PCM_DEMUXER_H

#include "common/common_pch.h"

class wav_pcm_demuxer_c: public wav_demuxer_c {
private:
  int m_bps;
  memory_cptr m_buffer;
  bool m_ieee_float;

public:
  wav_pcm_demuxer_c(wav_reader_c *reader, wave_header *wheader, bool ieee_float);

  virtual ~wav_pcm_demuxer_c();

  virtual int64_t get_preferred_input_size() {
    return m_bps;
  };

  virtual unsigned char *get_buffer() {
    return m_buffer->get_buffer();
  };

  virtual void process(int64_t len);
  virtual generic_packetizer_c *create_packetizer();

  virtual bool probe(mm_io_cptr &) {
    return true;
  };

  virtual unsigned int get_channels() const;
  virtual unsigned int get_sampling_frequency() const;
  virtual unsigned int get_bits_per_sample() const;
};

#endif  // MTX_INPUT_WAV_PCM_DEMUXER_H
