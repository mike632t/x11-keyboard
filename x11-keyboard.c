/*
 * x11-keyboard.c - Demonstrates how to handle key press events.
 *
 * Copyright(C) 2021   MT
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.   If not, see <http://www.gnu.org/licenses/>.
 *
 * 20 Sep 21   0.1   - Initial version - MT
 *
 */

#define  NAME          "x11-keyboard"
#define  VERSION       "0.1"
#define  BUILD         "0001"
#define  DATE          "20 Sep 21"
#define  AUTHOR        "MT"

#define  DEBUG 1       /* Enable/disable debug*/

#define  ASC_ESC 27    /* ASCII Escape */

#include <X11/Xlib.h>  /* XOpenDisplay(), etc. */
#include <X11/Xutil.h> /* XSizeHints etc. */

#include <ctype.h>     /* isalpha() */
#include <stdio.h>     /* fprintf(), etc. */

#include "gcc-debug.h" /* debug() */

int main(int argc, char **argv) {
   Display *h_display; /* Pointer to X display structure. */
   Window x_application_window; /* Application window structure. */
   XEvent x_event;

   int i_screen; /* Default screen number */
   int i_keysym;

   h_display = XOpenDisplay(NULL);
   if (h_display) {
      i_screen = DefaultScreen(h_display);
      x_application_window = XCreateSimpleWindow
         (h_display, RootWindow(h_display, i_screen), 100, 100, 400, 100, 1, BlackPixel(h_display, i_screen), WhitePixel(h_display, i_screen));
      XSelectInput
         (h_display, x_application_window, FocusChangeMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask | SubstructureNotifyMask); /* Select kind of events we are interested in. */
      XMapWindow
         (h_display, x_application_window); /* Show window on display */
      XRaiseWindow(h_display, x_application_window); /* Raise window - ensures expose event is raised? */
      XSync(h_display, False); /* Flush all pending requests to the X server, and wait until they are processed by the X server. */
      while (i_keysym != ASC_ESC) {
         while (XPending(h_display)) {
            XNextEvent(h_display, &x_event);
            switch (x_event.type) {
            case Expose:
               break;
            case KeyPress:
               i_keysym = XKeycodeToKeysym(h_display, x_event.xkey.keycode, 0);
               switch (i_keysym) {
               /* Keyboard Modifier keys */
               case XK_Control_L:
               case XK_Control_R:
               case XK_Shift_L:
               case XK_Shift_R:
               case XK_Alt_L: /* Alt */
               case XK_ISO_Level3_Shift: /* Alt Gr */
               case XK_Super_L: /* Left windows key */
               case XK_Super_R: /* Right windows key */
               case XK_Menu: /* Menu key */
               case XK_Num_Lock:
               case XK_Caps_Lock:
                  i_keysym = 0x00; /* Ignored */
                  break;
               /* ASCII control keys (chosen to map to ASCII - see keysymdef.h) */
               case XK_Escape:
               case XK_BackSpace:
               case XK_Tab:
               case XK_Linefeed:
               case XK_Clear:
               case XK_Return:
               case XK_Pause:
               case XK_Scroll_Lock:
               case XK_Sys_Req:
               case XK_Delete:
                  i_keysym &= 0x1f;
                  debug(printf("0x%04x 0x%04x (0x%02x)\n", x_event.xkey.state, x_event.xkey.keycode, i_keysym));
                  break;
               /* Keypad function keys */
               case  XK_KP_F1:
               case  XK_KP_F2:
               case  XK_KP_F3:
               case  XK_KP_F4:
               case  XK_KP_Home:
               case  XK_KP_Left:
               case  XK_KP_Up:
               case  XK_KP_Right:
               case  XK_KP_Down:
               case  XK_KP_Page_Up:
               case  XK_KP_Page_Down:
               case  XK_KP_End:
               case  XK_KP_Begin:
               case  XK_KP_Insert:
               case  XK_KP_Delete:
               case  XK_KP_Equal:
                  if (!(x_event.xkey.state & Mod2Mask) != !(x_event.xkey.state & ShiftMask)) { /* If numlock or shift (but not both) is pressed check number*/
                     i_keysym = XKeycodeToKeysym(h_display, x_event.xkey.keycode, 1); 
                     switch (i_keysym) {
                     case  XK_KP_Tab:
                     case  XK_KP_Enter:
                     case  XK_KP_Multiply:
                     case  XK_KP_Add:
                     case  XK_KP_Separator:
                     case  XK_KP_Subtract:
                     case  XK_KP_Decimal:
                     case  XK_KP_Divide:
                     case  XK_KP_0:
                     case  XK_KP_1:
                     case  XK_KP_2:
                     case  XK_KP_3:
                     case  XK_KP_4:
                     case  XK_KP_5:
                     case  XK_KP_6:
                     case  XK_KP_7:
                     case  XK_KP_8:
                     case  XK_KP_9:
                        i_keysym &= 0x7f;
                        break;
                     }
                  }
                  else
                     i_keysym = 0x00; /* Ignore keypad function keys*/
                     debug(printf("0x%04x 0x%04x (0x%02x) '%c'\n", x_event.xkey.state, x_event.xkey.keycode, i_keysym, i_keysym));
                  break;
               /* Keypad numbers chosen to map to ASCII - see keysymdef.h) */case  XK_KP_Space:
               case  XK_KP_Tab:
               case  XK_KP_Enter:
               case  XK_KP_Multiply:
               case  XK_KP_Add:
               case  XK_KP_Separator:
               case  XK_KP_Subtract:
               case  XK_KP_Decimal:
               case  XK_KP_Divide:
                  i_keysym &= 0x7f;
                  debug(printf("0x%04x 0x%04x (0x%02x) '%c'\n", x_event.xkey.state, x_event.xkey.keycode, i_keysym, i_keysym));
                  break;                               

               default:
                  if (isalpha(i_keysym)) { /* For alpha keys check both caps lock and shift */
                     if (!(x_event.xkey.state & ShiftMask) != !(x_event.xkey.state & LockMask)) 
                        i_keysym = XKeycodeToKeysym(h_display, x_event.xkey.keycode, 1);
                  }
                  else {
                     if (x_event.xkey.state & ShiftMask)
                        i_keysym = XKeycodeToKeysym(h_display, x_event.xkey.keycode, 1);
                  }
                  
                  if (x_event.xkey.state & ControlMask) {
                     i_keysym = XKeycodeToKeysym(h_display, x_event.xkey.keycode, 1);
                     debug(printf("0x%04x 0x%04x (0x%02x) '%c'\n", x_event.xkey.state, x_event.xkey.keycode, i_keysym, i_keysym));
                     if (((i_keysym >= '@') && (i_keysym <= '_')) || ((i_keysym >= 'a') && (i_keysym <= 'z'))) { /* Only modify valid control keys */
                        i_keysym &= 0x1f;
                        debug(printf("0x%04x 0x%04x (0x%02x)\n", x_event.xkey.state, x_event.xkey.keycode, i_keysym));
                     }
                  }
                  else {
                     debug(printf("0x%04x 0x%04x (0x%02x) '%c'\n", x_event.xkey.state, x_event.xkey.keycode, i_keysym, i_keysym & 0x7f));
                  }
               }
               if (isprint(i_keysym))
                  printf("0x%04x 0x%04x (0x%02x) '%c'\n", x_event.xkey.state, x_event.xkey.keycode, i_keysym, i_keysym);
               else
                  printf("0x%04x 0x%04x (0x%02x)\n", x_event.xkey.state, x_event.xkey.keycode, i_keysym);
               break;
            default:
               break;
            }
         }
      }
      XCloseDisplay(h_display);
   }
   else {
      fprintf(stderr, "%s: cannot connect to X server.\n", argv[0]);
   }
   return(0);
}
