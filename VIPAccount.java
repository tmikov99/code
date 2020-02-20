package kontrolnoBank;

public class VIPAccount extends Account{
	@Override
	protected void reduceMoney(double amount) {
		changeAmount(amount*(-1));
	}
}
