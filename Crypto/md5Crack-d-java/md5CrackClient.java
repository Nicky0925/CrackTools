import java.net.*;
import java.io.*;

public class md5CrackClient {
    public static final int PORT = 5555;
    public static void main(String[] args) {

        if(args[0] == null) {
            System.out.println("サーバを指定してください");
            System.exit(1);
        }
        
        Socket socket = null;
        try{
            socket = new Socket(args[0], PORT);
            System.out.println("解析したいハッシュを入力してください");
            PrintWriter pw = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            pw.println(br.readLine());
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String msg = in.readLine();
            pw.close();
            br.close();
            in.close();
            System.out.println(msg);
        }catch(IOException e){
            System.out.println(e);
        }

    }
}