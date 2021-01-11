import java.net.*;
import java.io.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class md5CrackServer {
  public static final int PORT = 5555;
  public static final int HASHLEN = 32;

  // ハッシュ値の比較
  //成功したらrow, 失敗したら-1を返す
  static int md5Hash(String str, String file) {

    int row = 0;
    String line = null;
    String strHash = null;
    boolean flag = false;
    
    try {
      BufferedReader br = new BufferedReader(new FileReader(file));
      StringBuffer sb = new StringBuffer();
      while((line = br.readLine()) != null) {
        //flagがtrueならば解析成功
        if(flag == true) {
          break;
        }
        //前のハッシュ値を削除
        sb.delete(0, sb.length());
        //ハッシュ値を求める
        MessageDigest md5 = MessageDigest.getInstance("MD5");
        byte[] resultBytes = md5.digest(line.getBytes());
        //byteから16進文字列へ変換
        for(int i = 0; i < resultBytes.length; i++) {
          sb.append(String.format("%02x", resultBytes[i]));
        }
        strHash = sb.toString();
        System.out.println(str);
        System.out.println(strHash);
        //ハッシュ値の比較 str == file.hash
        for(int i = 0; i < HASHLEN; i++) {
          if(str.charAt(i) != strHash.charAt(i)){
            flag = false;
            break;
          }
          flag = true;
        }
        row++;
      }
    }catch(IOException err){
      System.out.println(err);
    }catch(NoSuchAlgorithmException x){
      System.out.println(x);
    }
    
    if(flag) {
      return row;
    } else {
      return -1;
    }

  }

  //指定した行の文字列を取得
  public static String getFile(int n, String file) {

    String line = null;
    try {
      BufferedReader br = new BufferedReader(new FileReader(file));
      for(int i = 0; i < n; i++) {
        line = br.readLine();
      }
      br.close();
    }catch(IOException e){
      System.out.println(e);
    }
    return line;
    
  }

  public static void main(String[] args) {

    ServerSocket serverSocket = null;
    Socket socket = null;
    int ansLine = 0;
    String str = null; //クライアントからの文字列
    String sendStr = null;
    String hashFile = "test.txt";

    try {
      serverSocket = new ServerSocket(PORT);
      socket = serverSocket.accept();
      BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
      OutputStreamWriter out = new OutputStreamWriter(socket.getOutputStream());
      str = in.readLine();
      ansLine = md5Hash(str, hashFile);

      if(ansLine == -1) {
        out.write("解析失敗　ハッシュ値が見つかりません");
      } else {
        sendStr = getFile(ansLine, hashFile);
        out.write("解析結果：" + sendStr);
      }

      out.close();
      socket.close();
    } catch(IOException e) {
      System.out.println(e);
    }

  }
}
