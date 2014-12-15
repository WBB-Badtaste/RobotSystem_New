using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using HPSocketCS;
using HPSocketCS.SDK;
using System.Runtime.InteropServices;

namespace Robot
{
    class Network
    {
        /// <summary>
        /// 目标地址
        /// </summary>
        public string TargetAddr { get; set; }

        /// <summary>
        /// 目标端口
        /// </summary>
        public ushort TargetPort { get; set; }

        /// <summary>
        /// TCP链路与RCID的对应数组
        /// </summary>
        private static List<IntPtr> tcpLines = new List<IntPtr>();

        protected TcpAgent agent = new TcpAgent();
        public Network()
        {
            agent.SetCallback(OnAgentPrepareConnect, OnAgentConnect, OnAgentSend, OnAgentReceive, OnAgentClose, OnAgentError, OnAgentShutdown);
            agent.Start("127.0.0.1", false);
        }

        ~Network()
        {
            agent.Stop();
        }

        public bool Connect(string targetAddr, ushort targetPort, int rcId)
        {
            IntPtr clientConnId = new IntPtr();
            if (agent.Connect(targetAddr, targetPort, ref clientConnId) == false)
            {
                if (agent.Connect(targetAddr, targetPort, ref clientConnId) == false)
                {
                    if (agent.Connect(targetAddr, targetPort, ref clientConnId) == false)
                    {
                        return false;
                    }
                }
            }
            while (tcpLines.Count() < rcId + 1)
            {
                tcpLines.Add(IntPtr.Zero);
            }
            tcpLines[rcId] = clientConnId;
            return true;
        }

        public bool Disconnect(int rcId, bool force = true)
        {
            IntPtr clientConnId = tcpLines[rcId];
            if (agent.Disconnect(clientConnId, force))
            {
                tcpLines[rcId] = IntPtr.Zero;
                return true;
            }
            return false;
        }

        public bool SendTargets(int rcId, Target[] pTargets, ushort num)
        {
            IntPtr clientConnId = tcpLines[rcId];
            if (clientConnId == IntPtr.Zero) return false;

            double dBuffer = 0;
            string sBuffer = "\x54";
            byte[] str = new byte[5];
            for (int i = 0; i < num; ++i)
            {
                sBuffer += string.Format("{0}{1}{2}{3}", pTargets[i].ID / 1000, pTargets[i].ID / 100 % 10, pTargets[i].ID / 10 % 10, pTargets[i].ID % 10);
                str = Encoding.Default.GetBytes(sBuffer);
                if (pTargets[i].PosX >= 0)
                {
                    str=Combine(str, new byte[] { 0xAA });
                    dBuffer = pTargets[i].PosX;
                }
                else
                {
                    str = Combine(str, new byte[] { 0x55 });
                    dBuffer = -pTargets[i].PosX;
                }
                sBuffer = string.Format("{0}{1}{2}{3}{4}{5}", (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10, (long)(dBuffer / 0.01) % 10);
                str = AddStringToBytes(str, sBuffer);
                if (pTargets[i].PosY >= 0)
                {
                    str = Combine(str, new byte[] { 0xAA });
                    dBuffer = pTargets[i].PosY;
                }
                else
                {
                    str = Combine(str, new byte[] { 0x55 });
                    dBuffer = -pTargets[i].PosY;
                }
                sBuffer = string.Format("{0}{1}{2}{3}{4}{5}", (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10, (long)(dBuffer / 0.01) % 10);
                str = AddStringToBytes(str, sBuffer);                
                if (pTargets[i].Aangle >= 0)
                {
                    str = Combine(str, new byte[] { 0xAA });
                    dBuffer = pTargets[i].Aangle;
                }
                else
                {
                    str = Combine(str, new byte[] { 0x55 });
                    dBuffer = -pTargets[i].Aangle;
                }
                sBuffer = string.Format("{0}{1}{2}{3}", (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10);
                str = AddStringToBytes(str, sBuffer);
                if (pTargets[i].EncoderValue >= 0)
                {
                    str = Combine(str, new byte[] { 0xAA });
                    dBuffer = pTargets[i].EncoderValue;
                }
                else
                {
                    str = Combine(str, new byte[] { 0x55 });
                    dBuffer = -pTargets[i].EncoderValue;
                }
                sBuffer = string.Format("{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}", (long)dBuffer / 1000000000 % 10, (long)dBuffer / 100000000 % 10, (long)dBuffer / 10000000 % 10, (long)dBuffer / 1000000 % 10, (long)dBuffer / 100000 % 10, (long)dBuffer / 10000 % 10, (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10);
                str = AddStringToBytes(str, sBuffer);
            }

            str = Bale(str);
            agent.Send(clientConnId, str, str.Length);
            return true;
        }

        byte[] AddStringToBytes(byte[] bytes, string str)
        {
            bytes = Combine(bytes, Encoding.Default.GetBytes(str));
            return bytes;
        }

        byte[] Combine(byte[] first, byte[] second)
        {
            byte[] ret = new byte[first.Length + second.Length];
            Buffer.BlockCopy(first, 0, ret, 0, first.Length);
            Buffer.BlockCopy(second, 0, ret, first.Length, second.Length);
            return ret;
        }

        byte[] Bale(byte[] str)
        {
            string sBuffer = "\x02";
            ushort id = GeneratePacketID();
            sBuffer += string.Format("{0}{1}{2}{3}{4}{5}{6}{7}", id / 1000, id / 100 % 10, id / 10 % 10, id % 10, str.Count() / 1000, str.Count() / 100 % 10,str.Count() / 10 % 10,str.Count() % 10);
            byte[] bBuffer = Encoding.Default.GetBytes(sBuffer);
            str = Combine(bBuffer,str);
            str = Combine(str, new byte[]{0xFF,0xFF,0x03});
            return str;
        }

        static ushort m_packetID = 0;
        ushort GeneratePacketID() { return ++m_packetID; }

        /// <summary>
        /// 准备连接了
        /// </summary>
        /// <param name="dwConnId"></param>
        /// <param name="socket"></param>
        /// <returns></returns>
        protected virtual HandleResult OnAgentPrepareConnect(IntPtr dwConnId, uint socket)
        {
            return HandleResult.Ok;
        }

        /// <summary>
        /// 已连接
        /// </summary>
        /// <param name="dwConnId"></param>
        /// <returns></returns>
        protected virtual HandleResult OnAgentConnect(IntPtr dwConnId)
        {
            return HandleResult.Ok;
        }
        
        /// <summary>
        /// 客户端发数据了
        /// </summary>
        /// <param name="dwConnId"></param>
        /// <param name="pData"></param>
        /// <param name="iLength"></param>
        /// <returns></returns>
        protected virtual HandleResult OnAgentSend(IntPtr dwConnId, IntPtr pData, int iLength)
        {
            return HandleResult.Ok;
        }

        /// <summary>
        /// 数据到达了
        /// </summary>
        /// <param name="dwConnId"></param>
        /// <param name="pData"></param>
        /// <param name="iLength"></param>
        /// <returns></returns>
        protected virtual HandleResult OnAgentReceive(IntPtr dwConnId, IntPtr pData, int iLength)
        {
            return HandleResult.Ok;
        }

        /// <summary>
        /// 连接关闭了
        /// </summary>
        /// <param name="dwConnId"></param>
        /// <returns></returns>
        protected virtual HandleResult OnAgentClose(IntPtr dwConnId)
        {
            return HandleResult.Ok;
        }

        /// <summary>
        /// 出错了
        /// </summary>
        /// <param name="dwConnId"></param>
        /// <param name="enOperation"></param>
        /// <param name="iErrorCode"></param>
        /// <returns></returns>
        protected virtual HandleResult OnAgentError(IntPtr dwConnId, SocketOperation enOperation, int iErrorCode)
        {
            // 因为要释放附加数据,所以直接返回OnAgentClose()了
            return OnAgentClose(dwConnId);
        }

        /// <summary>
        /// Agent关闭了
        /// </summary>
        /// <returns></returns>
        protected virtual HandleResult OnAgentShutdown()
        {
            return HandleResult.Ok;
        }
    }
}
