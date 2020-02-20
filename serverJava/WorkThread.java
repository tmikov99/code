package failchetest;

import java.io.EOFException;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

public class WorkThread extends Thread{
	Socket sock;

    WorkThread(Socket sock) {
        this.sock = sock;
    }
	@Override
	public void run() {
		try {
			ObjectInputStream fileInput = new ObjectInputStream(new FileInputStream("tekst.txt"));
			Scanner input = new Scanner(sock.getInputStream());
			PrintStream output = new PrintStream(sock.getOutputStream());
			ArrayList<Question> questions = new ArrayList<Question>();
			int score = 0, max = 0;
			while(true) {
				try {
			Question q = (Question)fileInput.readObject();
			if(q==null) {
				System.out.println("Vlaza u breika");
				break;
			}
			questions.add(q);
			
			}catch(EOFException e) {
				System.out.println("Done reading");
				break;
			}
			}
			for(Question temp:questions) {
				output.println("Asking question");
				++max;
				if(temp.ask(input,output))
					++score;
			}
			output.println("Test complete");
			output.println("You answered " +score + " correctly out of a possible maximum of " +max);
	}catch(IOException|ClassNotFoundException e) {
		e.printStackTrace();
	}
	}
}
