/*
  mkvmerge -- utility for splicing together matroska files
  from component media subtypes

  Distributed under the GPL v2
  see the file COPYING for details
  or visit http://www.gnu.org/copyleft/gpl.html

  EBML/XML converter specialization for tags

  Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#pragma once

#include "common/common_pch.h"

#include <matroska/KaxTags.h>

#include "common/tags/tags.h"
#include "common/xml/ebml_converter.h"

namespace mtx::xml {

class ebml_tags_converter_c: public ebml_converter_c {
public:
  ebml_tags_converter_c();
  virtual ~ebml_tags_converter_c();

protected:
  virtual void fix_ebml(libebml::EbmlMaster &root) const;
  virtual void fix_tag(libmatroska::KaxTag &tag) const;

  void setup_maps();

public:
  static void write_xml(libmatroska::KaxTags &tags, mm_io_c &out);
  static std::shared_ptr<libmatroska::KaxTags> parse_file(std::string const &file_name, bool throw_on_error);
};

}
