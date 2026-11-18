#pragma once
// A small transparent strip on the taskbar, just left of the notification area, showing
// "[icon] 30%  [icon] 93%". Implemented as a layered child window of the taskbar (Shell_TrayWnd), with a
// copy on each secondary-monitor taskbar (Shell_SecondaryTrayWnd) next to its clock.
#include <windows.h>
#include <string>
#include <vector>
#include "brands.h"
#include "devices.h"

struct WidgetItem {
    DeviceKind kind = DeviceKind::Other;
    int  percent  = -1;     // -1 = unknown
    std::wstring text;      // shown instead of the percentage when set (coarse levels like "Low")
    bool charging = false;
    bool dim      = false;  // asleep / stale value
    bool low      = false;
    bool bluetooth = false;  // picks the Bluetooth icon when the device type is unknown
    Accent accent  = Accent::None;
};

namespace widget {
// Creates the widget on the primary taskbar, plus a copy on each other monitor's taskbar. Clicks are reported by posting `clickMsg` to `notifyWnd`.
bool Create(HINSTANCE inst, HWND notifyWnd, UINT clickMsg, bool lightTheme);
void Destroy();
bool Alive();
void SetItems(const std::vector<WidgetItem>& items, const std::wstring& tooltip);
void SetLightTheme(bool light);
// Draws a rounded plate in the taskbar's colours behind the text (kept across Create/Destroy).
void SetBackground(bool on);
// Re-checks the taskbar layout and moves the widget if needed; call about once a second.
// Returns false when the taskbar it was attached to is gone.
bool Reposition();
// Draws `items` the way the widget would, on an opaque taskbar-coloured strip `height` pixels tall,
// at the given DPI (for --preview: checking the colours on both themes). Returns BGRA pixels.
std::vector<DWORD> RenderStrip(const std::vector<WidgetItem>& items, bool light, int dpi, int height, int& width);
}
