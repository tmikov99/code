package failchetest;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class FailcheTest {
	public static int listeningPort = 1211;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		ServerSocket ss = null;
		try {
			ss = new ServerSocket(listeningPort);
			System.out.println("Server started");
			while(true) {
				Socket sock = ss.accept();
				new WorkThread(sock).start();
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			if(ss!=null)
				ss.close();
		}
			
	}
}
