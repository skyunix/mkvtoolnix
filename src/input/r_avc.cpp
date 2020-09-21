/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL v2
   see the file COPYING for details
   or visit https://www.gnu.org/licenses/old-licenses/gpl-2.0.html

   AVC/h2.64 ES demultiplexer module

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#include "common/common_pch.h"

#include "common/byte_buffer.h"
#include "common/codec.h"
#include "common/error.h"
#include "common/memory.h"
#include "common/id_info.h"
#include "input/r_avc.h"
#include "merge/input_x.h"
#include "merge/file_status.h"
#include "output/p_avc_es.h"

debugging_option_c avc_es_reader_c::ms_debug{"avc_reader"};

bool
avc_es_reader_c::probe_file() {
  int num_read, i;
  bool first = true;

  mtx::avc::es_parser_c parser;
  parser.ignore_nalu_size_length_errors();
  parser.set_nalu_size_length(4);

  for (i = 0; 50 > i; ++i) {
    num_read = m_in->read(m_buffer->get_buffer(), m_buffer->get_size());
    if (4 > num_read)
      return 0;

    // MPEG TS starts with 0x47.
    if (first && (0x47 == m_buffer->get_buffer()[0]))
      return 0;
    first = false;

    parser.add_bytes(m_buffer->get_buffer(), num_read);

    if (!parser.headers_parsed())
      continue;

    m_width  = parser.get_width();
    m_height = parser.get_height();

    if ((0 >= m_width) || (0 >= m_height))
      return false;

    return true;
  }

  return false;
}

void
avc_es_reader_c::read_headers() {
  show_demuxer_info();
}

void
avc_es_reader_c::create_packetizer(int64_t) {
  if (!demuxing_requested('v', 0) || (NPTZR() != 0))
    return;

  add_packetizer(new avc_es_video_packetizer_c(this, m_ti));
  PTZR0->set_video_pixel_dimensions(m_width, m_height);

  show_packetizer_info(0, PTZR0);
}

file_status_e
avc_es_reader_c::read(generic_packetizer_c *,
                      bool) {
  if (m_in->getFilePointer() >= m_size)
    return FILE_STATUS_DONE;

  int num_read = m_in->read(m_buffer->get_buffer(), m_buffer->get_size());
  if (0 < num_read)
    PTZR0->process(new packet_t(memory_c::borrow(m_buffer->get_buffer(), num_read)));

  return (0 != num_read) && (m_in->getFilePointer() < m_size) ? FILE_STATUS_MOREDATA : flush_packetizers();
}

void
avc_es_reader_c::identify() {
  auto info = mtx::id::info_c{};
  info.add(mtx::id::packetizer, mtx::id::mpeg4_p10_es_video);

  id_result_container();
  id_result_track(0, ID_RESULT_TRACK_VIDEO, codec_c::get_name(codec_c::type_e::V_MPEG4_P10, "MPEG-4 part 10 ES"), info.get());
}
