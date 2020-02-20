package failchetest;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.Serializable;
import java.util.Scanner;

public class Question implements Serializable{
	public static final float serialVersionUTD = 1L;
	public String text;
	public String[] answers;
	public int correctAnswer;
	public Question(String text, String[] answers, int correctAnswer) {
		this.text = text;
		this.answers = answers;
		this.correctAnswer = correctAnswer;
	}
	public void print() {
		System.out.println(text);
		for(int i=0, len=answers.length;i<len;++i) {
			System.out.println((i+1)+")"+answers[i]);
		}
	}
	public void print(PrintStream out) throws IOException {
		out.println(text);
		for(int i=0, len=answers.length;i<len;++i) {
			out.println((i+1)+")"+answers[i]);
		}
	}
	public boolean ask() {
		this.print();
		Scanner sc = new Scanner(System.in);
		int answer;
		do {
		System.out.println("Enter your answer");
		answer = sc.nextInt();
		}while(answer>answers.length||answer<1);
		if (answer == correctAnswer)
			return true;
		else return false;
	}
	public boolean ask(Scanner in, PrintStream out) throws IOException {
		this.print(out);
		int answer;
		do {
		out.println("Enter your answer");
		answer = Integer.parseInt(in.nextLine());
		System.out.println(answer);
		}while(answer>answers.length||answer<1);
		if (answer == correctAnswer) {
			out.println("Correct answer");
			return true;
		}
		else {
			out.println("Incorrect answer");
			return false;
		}
	}
}
