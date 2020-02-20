package kontrolnoBank;

public class Bank {
	private String name;
	private String town;
	private int number;
	public Bank(String name,String town,int number) {
		this.name = name;
		this.town = town;
		this.number = number;
	}
	public String getName() {
		return name;
	}
	public String getTown() {
		return town;
	}
	public int getNumber() {
		return number;
	}
	public void setNumber(int number) {
		this.number = number;
	}
}
