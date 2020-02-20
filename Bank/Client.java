package kontrolnoBank;

public class Client {
	String name;
	String EGN;
	Account[] accounts;
	public Client(String name,String EGN) {
		this.name = name;
		this.EGN = EGN;
		accounts = new Account[100];
	}
	public void addAccount(Account newAcc) {
		for(int i=0;i<accounts.length;i++) {
			if(accounts[i]==null) {
				accounts[i]=newAcc;
				return;
			}
			
		}
		System.out.println("No more accounts allowed");
	}
	public void deleteAccount(int index) {
		if(index>=accounts.length) {
			System.out.println("Index is out of bounds");
			return;
		}
		accounts[index]=null;
		for(int i=index;i<accounts.length-1;i++) {
			accounts[i]=accounts[i+1];
			accounts[i+1]=null;
		}
	}
}
