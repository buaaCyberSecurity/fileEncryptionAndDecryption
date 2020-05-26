import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class FileTransferUtil {

    public static void main(String[] args) {
        // 创建 JFrame 实例
        JFrame frame = new JFrame("fileTrans");
        // Setting the width and height of frame
        frame.setSize(600, 500);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        /* 创建面板，这个类似于 HTML 的 div 标签
         * 我们可以创建多个面板并在 JFrame 中指定位置
         * 面板中我们可以添加文本字段，按钮及其他组件。
         */
        JPanel panel = new JPanel();
        // 添加面板
        frame.add(panel);
        /*
         * 调用用户定义的方法并添加组件到面板
         */
        placeComponents(frame, panel);

        // 设置界面可见
        frame.setVisible(true);
    }

    private static void placeComponents(JFrame frame, JPanel panel) {
        /* 布局部分我们这边不多做介绍
         * 这边设置布局为 null
         */
        panel.setLayout(null);

        final File[] file = new File[1];

        //文本框
        JLabel label1 = new JLabel("Input IP:");
        label1.setBounds(10, 10, 100, 30);
        panel.add(label1);
        JTextField textField1 = new JTextField();
//        String name = "like:\"0.0.0.0\"";
//        textField1.addFocusListener(new FocusListener() {
//            @Override
//            public void focusGained(FocusEvent arg0) {
//                // TODO Auto-generated method stub
//                if (textField1.getText() == name || name.equals(textField1.getText()))
//                    textField1.setText("");
//            }
//
//            @Override
//            public void focusLost(FocusEvent arg0) {
//                // TODO Auto-generated method stub
//                if (textField1.getText() == "" || textField1.getText().equals(""))
//                    textField1.setText(name);
//            }
//
//        });
        textField1.setBounds(110, 10, 305, 30);
        panel.add(textField1);

        //文本框
        JLabel label2 = new JLabel("Input Port:");
        label2.setBounds(10, 50, 100, 30);
        panel.add(label2);
        JTextField textField2 = new JTextField("");
        textField2.setBounds(110, 50, 305, 30);
        panel.add(textField2);

        //标签说明
        JLabel label = new JLabel("Algorithm:");
        label.setBounds(10, 90, 100, 30);
        panel.add(label);
        // 将codejson数据放入选择框
        JComboBox<String> comboBox = new JComboBox<String>();
        comboBox.setBounds(110, 90, 305, 30);
        comboBox.addItem("AES"); //下拉选填充数据
        comboBox.addItem("DES"); //下拉选填充数据
        panel.add(comboBox);


        //标签说明
        JLabel label3 = new JLabel("Send file:");
        label3.setBounds(10, 150, 100, 30);
        panel.add(label3);
        //选择文件
        JTextField textField3 = new JTextField("");
        textField3.setBounds(120, 180, 430, 30);
        panel.add(textField3);
        // 创建按钮
        JButton getFilebutton = new JButton("File:");
        getFilebutton.setBounds(10, 180, 100, 30); //位置信息
        panel.add(getFilebutton);//将按钮放入容器
        getFilebutton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                JFileChooser jfc = new JFileChooser();
                jfc.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
                jfc.showDialog(new JLabel(), "Select");
                file[0] = jfc.getSelectedFile();
                textField3.setText(file[0].getAbsolutePath());
            }
        });

        // 创建按钮
        JButton send = new JButton("Send");
        send.setBounds(220, 220, 100, 30); //位置信息
        panel.add(send);//将按钮放入容器
        send.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
//                    exec("chmod +777 ./run.sh");
                    System.out.println("chmod success");
                    String cmd = "./sender/send \"" + textField1.getText() + "\" " + textField2.getText() + " " + textField3.getText();
                    System.out.println(cmd);
                    exec(cmd);
                    System.out.println("send success");
                    frame.dispose();
                    System.exit(0);
                } catch (Exception e1) {
                    e1.printStackTrace();
                    frame.dispose();
                    System.exit(0);
                }
            }
        });


        //标签说明
        JLabel label4 = new JLabel("Receive file:");
        label4.setBounds(10, 280, 100, 30);
        panel.add(label4);
        JButton rec = new JButton("Rec");
        rec.setBounds(110, 280, 100, 30); //位置信息
        panel.add(rec);//将按钮放入容器
        rec.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    exec("./receiver/rec \"" + textField1.getText() + "\" " + textField2.getText());
                    System.out.println("receive success");
                    frame.dispose();
                    System.exit(0);
                } catch (IOException e1) {
                    e1.printStackTrace();
                } catch (InterruptedException e1) {
                    e1.printStackTrace();
                    frame.dispose();
                    System.exit(0);
                }
            }
        }) ;

    }

    public static boolean exec(String cmd) throws IOException, InterruptedException {
        String[] cmds = {"/bin/sh",
                "-c", cmd};
        Process process = Runtime.getRuntime().exec(cmds);

        //消费正常日志
        clearStream(process.getInputStream());
        //消费错误日志
        clearStream(process.getErrorStream());

        //i为返回值，判断是否执行成功
        int i = process.waitFor();
        if (i != 0) {
            //logger.error("Failed to call shell command and the return status's is: {}", i);
            return false;
        }

        return true;
    }

    private static void clearStream(InputStream stream) {
        //处理buffer的线程
        new Thread() {
            @Override
            public void run() {

                String line = null;

                try (BufferedReader in = new BufferedReader(new InputStreamReader(stream));) {
                    while ((line = in.readLine()) != null) {
                        //logger.debug(line);
                    }
                } catch (IOException e) {
                    //logger.error("exec error : {}", e);
                }
            }
        }.start();
    }

}

