using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server_Interface
{
    public enum CP_Code
    {
        CP_CODE_CONNECT = 0,
        CP_CODE_CONSOLE,
        CP_CODE_TOTALWATER,
        CP_CODE_TOTALPOWER,
        CP_CODE_GETCLIENTS,
        CP_CODE_SETCLIENT,
        CP_CODE_DISABLEALLCLIENTS
    };
}
