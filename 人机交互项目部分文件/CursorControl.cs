using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Map
{
    class CursorControl
    {

        const int MOUSEEVENTF_MOVE = 0x0001; //移动鼠标
        const int MOUSEEVENTF_LEFTDOWN = 0x0002; //模拟鼠标左键按下
        const int MOUSEEVENTF_LEFTUP = 0x0004;// 模拟鼠标左键抬起
        const int MOUSEEVENTF_RIGHTDOWN = 0x0008; //模拟鼠标右键按下
        const int MOUSEEVENTF_RIGHTUP = 0x0010;// 模拟鼠标右键抬起
        const int MOUSEEVENTF_MIDDLEDOWN = 0x0020; //模拟鼠标中键按下
        const int MOUSEEVENTF_MIDDLEUP = 0x0040; //模拟鼠标中键抬起
        const int MOUSEEVENTF_ABSOLUTE = 0x8000; //标示是否采用绝对坐标

        [DllImport("user32.dll")]  
        static extern bool SetCursorPos(int x, int y);

        [DllImport("user32.dll")]  
        static extern bool mouse_event(int dwFlags, int dx, int dy, int dwData, UInt64 dwExtraInfo);

        static public void ClickLeftMoveCursor(int x,int y)
        {
            mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
        }
    }
}
