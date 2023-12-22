package org.example;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main {
    // This is where the interface of the C function that will be called through JNI is declared
    public native void writeToAccountingFile();

    static {
        // We load the C library "libmain.so"
        System.loadLibrary("main");
    }

    // We use these instance variables to pass data to the C library
    private int compensation;
    private String name;

    public static void main(String[] args) {
        // The program takes the HR data as a CSV file path as an argument
        if (args.length != 1) {
            System.out.println("Usage: cmd <csv-file-path>");
            System.exit(1);
        }

        String csvFilePath = args[0];

        // We read the CSV file line by line
        try (BufferedReader reader = new BufferedReader(new FileReader(csvFilePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] columns = line.split(",");

                String name = columns[0].trim();
                int number = Integer.parseInt(columns[1].trim());

                Main main = new Main();
                // Save the data of this CSV line in the instance variables to
                // pass as input to the C library
                main.compensation = number;
                main.name = name;
                // Call the C library
                main.writeToAccountingFile();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}