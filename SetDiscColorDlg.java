import java.awt.*; 
import java.awt.event.*; 
import javax.swing.*; 
class SetDiscColorDlg extends Dialog implements ActionListener 
{ 
Tower tower; 
JTextField maxtext,mintext,heighttext; 
JButton bgcolor,color,cancel; 
SetDiscColorDlg(JFrame f,Tower tower) 
{ super(f,"������ɫ ",true); 
setLayout(new FlowLayout()); 
this.tower=tower; bgcolor=new JButton(" ���ñ�����ɫ "); color=new JButton(" ����������ɫ "); cancel=new JButton(" �˳� "); add(bgcolor); 
add(color); 
add(cancel); 
bgcolor.addActionListener(this); 
color.addActionListener(this); 
cancel.addActionListener(this); 
setBounds(100,100,200,200); 
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
if(e.getSource()==bgcolor) 
{ Color newColor=JColorChooser.showDialog(this," ѡ�񱳾�ɫ ",new Color(200,226,226)); tower.setBackground(newColor); 
} 
else if(e.getSource()==color) 
{ Color newColor=JColorChooser.showDialog(this," ѡ�񱳾�ɫ ",new Color(200,226,226)); 
tower.color=newColor; 
tower.putDiscOnTower(); 
} 
else if(e.getSource()==cancel) 
{ 
setVisible(false); 
} 
} 
} 