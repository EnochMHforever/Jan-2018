import java.awt.*; 
import java.awt.event.*; 
import javax.swing.*; 
class SetDiscAcountDlg extends Dialog implements ActionListener 
{ 
JButton sure,cancel; 
Tower tower; 
JTextField text; 
SetDiscAcountDlg(JFrame f,Tower tower) 
{ super(f,"����������Ŀ ",true); 
this.tower=tower; 
Box box1=Box.createVerticalBox(); sure=new JButton(" ȷ�� "); cancel=new JButton(" �˳� "); 
text=new JTextField(5); 
Box box2=Box.createHorizontalBox(); 
box2.add(sure); 
box2.add(cancel); box1.add(new JLabel(" ������ 0-13 ֮����� ")); 
box1.add(text); 
box1.add(box2); 
add(box1); 
setBounds(100,100,210,100); 
sure.addActionListener(this); 
cancel.addActionListener(this); 
addWindowListener(new WindowAdapter() 
{ 
public void windowClosing(WindowEvent e) 
{ 
setVisible(false); 
} 
}); 
setVisible(true); 
} 
public void actionPerformed(ActionEvent e) 
{ 
if(e.getSource()==sure) 
{ 
try 
{ 
tower.amountOfDisc=Integer.valueOf(text.getText()); 
if(tower.amountOfDisc>0&&tower.amountOfDisc<13) 
{ 
tower.setAmountOfDisc(tower.amountOfDisc); 
tower.putDiscOnTower(); 
} 
else text.setText("�����뷶Χ�ڵ����� "); 
} 
catch(NumberFormatException en) 
{ text.setText("���������� (ÿ��ѡ�� )"); 
} 
} 
if(e.getSource()==cancel) 
{ 
setVisible(false); 
} 
} 
} 