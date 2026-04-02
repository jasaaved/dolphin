// Copyright 2015 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QEvent>
#include <QWindow>

class QMouseEvent;
class QTimer;

class RenderWidget final : public QWindow
{
  Q_OBJECT

public:
  explicit RenderWidget();

  bool event(QEvent* event) override;
  void showFullScreen();
  bool IsCursorLocked() const { return m_cursor_locked; }
  void SetCursorLockedOnNextActivation(bool locked = true);
  void SetWaitingForMessageBox(bool waiting_for_message_box);
  void SetCursorLocked(bool locked, bool follow_aspect_ratio = true);

signals:
  void EscapePressed();
  void Closed();
  void HandleChanged(void* handle);
  void StateChanged(bool fullscreen);
  void SizeChanged(int new_width, int new_height);
  void FocusChanged(bool focus);

private:
  void HandleCursorTimer();
  void OnHandleChanged(void* handle);
  void OnHideCursorChanged();
  void OnLockCursorChanged();
  void OnKeepOnTopChanged(bool top);
  void UpdateCursor();
  void PassEventToPresenter(const QEvent* event);
  void SetPresenterKeyMap();

  static constexpr int MOUSE_HIDE_DELAY = 3000;
  QTimer* m_mouse_timer;
  QPoint m_last_mouse{};
  int m_last_window_width = 0;
  int m_last_window_height = 0;
  float m_last_window_scale = 0;
  bool m_cursor_locked = false;
  bool m_lock_cursor_on_next_activation = false;
  bool m_waiting_for_message_box = false;
  bool m_should_unpause_on_focus = false;
};
