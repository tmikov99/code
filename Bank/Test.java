package kontrolnoBank;

public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Client client = new Client("Tosho","123");
		
		for(int i=100;i>0;i--) {
			VIPAccount vip=new VIPAccount();
			client.addAccount(vip);
		}
		for(int i=0;i<client.accounts.length;i++) {
			client.accounts[i].reduceMoney((double)i);
		}
		for(int i=0;i<client.accounts.length;i++) {
			if(client.accounts[i]==null) {
				break;
			}
			System.out.println(client.accounts[i].getMoney()+" #" +(i+1));
		}
		client.deleteAccount(45);
		for(int i=0;i<client.accounts.length;i++) {
			if(client.accounts[i]==null) {
				break;
			}
			System.out.println(client.accounts[i].getMoney()+" #" +(i+1));
		}
	}

}
