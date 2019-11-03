#pragma once

#include "common/common_pch.h"

#include "mkvtoolnix-gui/header_editor/value_page.h"

class QComboBox;

namespace mtx::gui::HeaderEditor {

class Tab;

class BoolValuePage: public ValuePage {
public:
  QComboBox *m_cbValue{};
  uint64_t m_originalValue{};

public:
  BoolValuePage(Tab &parent, PageBase &topLevelPage, EbmlMaster &master, EbmlCallbacks const &callbacks, translatable_string_c const &title, translatable_string_c const &description);
  virtual ~BoolValuePage();

  virtual QWidget *createInputControl() override;
  virtual QString originalValueAsString() const override;
  virtual QString currentValueAsString() const override;
  virtual void resetValue() override;
  virtual bool validateValue() const override;
  virtual void copyValueToElement() override;
};

}
