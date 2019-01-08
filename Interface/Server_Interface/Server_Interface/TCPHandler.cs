using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;

namespace Server_Interface
{
    public class WiFiHandler
    {
        private NetworkStream stream;
        private readonly IPAddress ipAdress;
        private bool isInDeserialize;

        public WiFiHandler(IPAddress ipAdress)
        {
            isInDeserialize = false;
            this.ipAdress = ipAdress ?? throw new NullReferenceException();

            Connect();
        }

        public bool Update()
        {
            if (stream.DataAvailable && !isInDeserialize)
            {
                string received = Receivemessage();
                received = received.Substring(received.IndexOf('^') + 1, received.IndexOf('&') - received.IndexOf('^') - 1);
                if (received == "MAINROAD")
                {
                    Sendmessage("ACK", stream);
                    Receivedata();
                    return true;
                }
            }
            return false;
        }

        public void SendSpeed(decimal value)
        {

            Sendmessage("DATA", stream);
            while (Receivemessage() != "ACK") { }
            Sendmessage("LIMIT:" + 0 + ',' + 0 + ',' + value, stream);
        }

        public void GetData()
        {
            Sendmessage("BEAT", stream);
        }

        public void Sendmessage(string message, NetworkStream stream)
        {
            Byte[] sendBytes = Encoding.ASCII.GetBytes(message);
            stream.Write(sendBytes, 0, sendBytes.Length);
            stream.Flush();

        }

        string Receivemessage()
        {
            byte[] bytesFrom = new byte[10025];

            stream.Read(bytesFrom, 0, bytesFrom.Length);
            string dataFromClient = Encoding.ASCII.GetString(bytesFrom);
            if (dataFromClient.Contains("\r"))
            {
                dataFromClient = dataFromClient.Substring(0, dataFromClient.IndexOf('\r'));
            }
            else
            {
                dataFromClient = dataFromClient.Substring(0, dataFromClient.IndexOf('\0'));
            }

            return dataFromClient;
        }

        public void Connect()
        {
            TcpClient clientSock = new TcpClient();
            Console.WriteLine("Connecting to Server ...");
            clientSock.Connect(ipAdress, 8888);

            stream = clientSock.GetStream();
            //this line sends 
            Sendmessage("interface", stream);
        }

        public void Receivedata()
        {

        }
    }
}
