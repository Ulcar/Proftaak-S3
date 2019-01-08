using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using System.Net.NetworkInformation;

namespace Server_Interface
{
    public class WiFiHandler
    {
        private NetworkStream stream;
        private readonly IPAddress ipAdress;
        private readonly int port;
        private string buffer;

        public WiFiHandler(IPAddress ipAdress, int port)
        {
            this.ipAdress = ipAdress ?? throw new NullReferenceException();
            this.port = port;

            Connect();
        }
        
        public void Sendmessage(string message)
        {
            Byte[] sendBytes = Encoding.ASCII.GetBytes(message);
            stream.Write(sendBytes, 0, sendBytes.Length);
            stream.Flush();
        }

        public void Connect()
        {
            TcpClient clientSock = new TcpClient();
            Console.WriteLine("Connecting to Server ...");
            clientSock.Connect(ipAdress, port);

            stream = clientSock.GetStream();
            if(!clientSock.Connected)
            {
                throw new ArgumentException("Wrong IPadress");
            }
            //this line sends 
            string firstMacAddress = NetworkInterface.GetAllNetworkInterfaces().Where(nic => nic.OperationalStatus == OperationalStatus.Up && nic.NetworkInterfaceType != NetworkInterfaceType.Loopback).Select(nic => nic.GetPhysicalAddress().ToString()).FirstOrDefault();
            List<string> message = new List<string> { firstMacAddress };

            Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_CONNECT, message));
        }

        public List<string> Receivedata()
        {
            List<string> messages = new List<string>();

            if (!stream.DataAvailable)
                return messages;

            UpdateBuffer();

            while(true)
            {
                int indexStart = buffer.IndexOf(Protocol.endCharToServer);
                int indexEind = buffer.IndexOf(Protocol.startCharToServer);

                if((indexStart == -1) || (indexEind == -1))
                    return messages;

                messages.Add(buffer.Substring(indexStart, indexEind - indexStart));
                buffer = buffer.Substring(indexEind, buffer.Length - indexEind);
            }

        }

        private void UpdateBuffer()
        {
            byte[] bytesFrom = new byte[10025];

            stream.Read(bytesFrom, 0, bytesFrom.Length);
            buffer += Encoding.ASCII.GetString(bytesFrom);
        }
    }
}
