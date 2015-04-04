#include "common/common_pch.h"

#include <QLineEdit>

#include "common/qt.h"
#include "mkvtoolnix-gui/header_editor/bit_value_page.h"

namespace mtx { namespace gui { namespace HeaderEditor {

using namespace mtx::gui;

BitValuePage::BitValuePage(Tab &parent,
                           PageBase &topLevelPage,
                           EbmlMaster &master,
                           EbmlCallbacks const &callbacks,
                           translatable_string_c const &title,
                           translatable_string_c const &description,
                           unsigned int bitLength)
  : ValuePage{parent, topLevelPage, master, callbacks, ValueType::String, title, description}
  , m_originalValue{128}
  , m_bitLength{bitLength}
{
}

BitValuePage::~BitValuePage() {
}

QWidget *
BitValuePage::createInputControl() {
  if (m_element)
    m_originalValue = bitvalue_c{*static_cast<EbmlBinary *>(m_element)};

  m_leText = new QLineEdit{this};
  m_leText->setText(getOriginalValueAsString());

  return m_leText;
}

QString
BitValuePage::getOriginalValueAsString()
  const {
  auto value = std::string{};
  auto data  = m_originalValue.data();

  if (data)
    for (auto end = data + (m_originalValue.size() / 8); data < end; ++data)
      value += (boost::format("%|1$02x|") % static_cast<unsigned int>(*data)).str();

  return Q(value);
}

QString
BitValuePage::getCurrentValueAsString()
  const {
  return m_leText->text();
}

void
BitValuePage::resetValue() {
  m_leText->setText(getOriginalValueAsString());
}

bool
BitValuePage::validateValue()
  const {
  try {
    auto bitValue = bitvalue_c{to_utf8(m_leText->text()), m_bitLength};
  } catch (...) {
    return false;
  }

  return true;
}

void
BitValuePage::copyValueToElement() {
  auto bitValue = bitvalue_c{to_utf8(m_leText->text()), m_bitLength};
  static_cast<EbmlBinary *>(m_element)->CopyBuffer(bitValue.data(), m_bitLength / 8);
}

}}}
