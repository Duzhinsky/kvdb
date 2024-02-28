package io.github.duzhinsky.kvdb;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class EchoClient {

    public static void main(String[] args) {
        try (Connection gc = new Connection("localhost", 1234)) {
            System.out.println(gc.sendCommand("get", "123"));
        }
    }
}

class Connection implements AutoCloseable {

    private final Socket clientSocket;
    private final PrintWriter out;
    private final BufferedReader in;

    public Connection(String ip, int port) {
        try {
            clientSocket = new Socket(ip, port);
            out = new PrintWriter(clientSocket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public String sendCommand(String cmd, String arg) {
        try {
            out.write((byte)(cmd.length()));
            out.print(cmd);
            out.write((byte)(arg.length()));
            out.println(arg);
            return in.readLine();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void close() {
        try {
            in.close();
            out.close();
            clientSocket.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}