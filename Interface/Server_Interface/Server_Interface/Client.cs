using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server_Interface
{
    class Client
    {
        public string MacAdress { get; private set; }
        public int ElecUsage { get; private set; }
        public int WaterUsage { get; private set; }
        public string CurrProgram { get; private set; }
        public bool Enabled { get; private set; }

        public Client(string macAdress, int elecUsage, int waterUsage, string currProgram, bool enabled)
        {
            MacAdress = macAdress;
            ElecUsage = elecUsage;
            WaterUsage = waterUsage;
            CurrProgram = currProgram;
            Enabled = enabled;
        }
    }
}
