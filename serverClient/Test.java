package clientche;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Scanner;

public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Socket sock;
        try {
            sock = new Socket("localhost", 1211);
        } catch (IOException ex) {
            System.out.println("Can't connect to server");
            return;
        }
        try {
        	Scanner sc = new Scanner(System.in);
        	Scanner input = new Scanner(sock.getInputStream());
        	PrintStream output = new PrintStream(sock.getOutputStream());
        	String message = "Asking question";
        	while(message.equals("Asking question")) {
	        	do {
		        	message = input.nextLine();
		        	System.out.println(message);
	        	}while(!message.equals("Enter your answer"));
	        	do {
		        	String answer = sc.nextLine();
		        	output.println(answer);
		        	message = input.nextLine();
		        	System.out.println(message);
	        	}while(!(message.equals("Correct answer")||message.equals("Incorrect answer")));
	        	message = input.nextLine();
	        }
        	System.out.println(message);
        	System.out.println(input.nextLine());
			sock.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
