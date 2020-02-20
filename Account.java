package kontrolnoBank;

public class Account {
	private double money = 0;
	public double getMoney() {
		return money;
	}
	protected void changeAmount(double amount) {
		money += amount;
	}
	protected void reduceMoney(double amount) {
		if(amount>money) {
			System.out.println("Nema Kinti");
		}
		else {
			changeAmount(amount*(-1));
		}
	}
}
