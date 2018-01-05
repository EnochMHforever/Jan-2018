import javax.swing.*; 
import java.awt.*; 
import java.awt.event.*; 
import java.util.*; 
import java.io.*; 
import java.net.*; 
import java.applet.*; 
public class HannoiWindow extends JFrame implements ActionListener { 
Tower tower = null; 
int amountOfDisc = 3; 
char[] towerName = { 'A', 'B', 'C' }; 
JMenuBar bar; 
JMenu menuGrade; 
boolean tag = true; int t = 0;// ���ڼ�ʱ�еı��� 
javax.swing.Timer secondTime; 
File file = new File("91.mid"); 
URL url; 
AudioClip clip; JMenu menusetDisc;// �������
JMenuItem setDiscAcount, setDiscWidth, setDiscColor; 
JMenu menumusic; 
JLabel timetext; 
JMenuItem oneGradeItem, twoGradeItem, threeGradeItem, musicstart,musicstop; 
JButton renew = null; 
JButton autoButton = null; 
JPanel center = new JPanel(); 
HannoiWindow() { t = 0;// ���ڼ�ʱ��
tower = new Tower(towerName); 
tower.setAmountOfDisc(amountOfDisc); 
tower.setMaxDiscWidth(120); 
tower.setMinDiscWidth(50); 
tower.setDiscHeight(16); 
tower.putDiscOnTower(); 
add(tower, BorderLayout.CENTER); 
bar = new JMenuBar(); menuGrade = new JMenu(" ѡ�񼶱� "); oneGradeItem = new JMenuItem(" ����"); twoGradeItem = new JMenuItem(" �м�"); threeGradeItem = new JMenuItem(" �߼�"); 
menuGrade.add(oneGradeItem); 
menuGrade.add(twoGradeItem); 
menuGrade.add(threeGradeItem); 
bar.add(menuGrade); 
menusetDisc = new JMenu(" �������� ");// �������
menumusic = new JMenu(" ���ñ������� "); 
setDiscColor = new JMenuItem(" ����������ɫ "); 
setDiscWidth = new JMenuItem(" �������Ӵ�С "); 
setDiscAcount = new JMenuItem(" ����������Ŀ "); 
musicstart = new JMenuItem(" �������ֿ��� "); 
musicstop = new JMenuItem(" �������ֹر� "); 
menusetDisc.add(setDiscColor); 
menusetDisc.add(setDiscAcount); 
menusetDisc.add(setDiscWidth); 
menumusic.add(musicstart); 
menumusic.add(musicstop); 
bar.add(menusetDisc); 
bar.add(menumusic); 
secondTime = new javax.swing.Timer(1000, this); 
secondTime.start(); 
timetext = new JLabel(); 
try { 
url = file.toURL(); 
clip = Applet.newAudioClip(url); 
} catch (Exception ex) { 
} 
clip.play(); 
tag = true; 
setJMenuBar(bar); setDiscColor.addActionListener(this);// ������ 3 �д���
setDiscWidth.addActionListener(this); 
setDiscAcount.addActionListener(this); 
musicstart.addActionListener(this); 
musicstop.addActionListener(this); 
oneGradeItem.addActionListener(this); 
twoGradeItem.addActionListener(this); 
threeGradeItem.addActionListener(this); renew = new JButton(" ���¿�ʼ "); 
renew.addActionListener(this); autoButton = new JButton(" �Զ���ʾ "); 
autoButton.addActionListener(this); 
JPanel north = new JPanel(); 
JPanel south = new JPanel();// /////////////////////// 
south.add(timetext); 
north.add(renew); 
north.add(autoButton); String mess = " ��ȫ�����Ӵ� " + towerName[0] + " �����˵� " + towerName[1] + " �� ��" + towerName[2] + " ��"; 
JLabel hintMess = new JLabel(mess, JLabel.CENTER); 
north.add(hintMess); 
add(north, BorderLayout.NORTH); 
add(south, BorderLayout.SOUTH); 
setResizable(false); 
setVisible(true); 
setBounds(60, 60, 460, 410); 
validate(); 
setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
} 
public void actionPerformed(ActionEvent e) { 
if (e.getSource() == oneGradeItem) { 
amountOfDisc = 3; 
tower.setAmountOfDisc(amountOfDisc); 
tower.putDiscOnTower(); 
t = 0; 
} else if (e.getSource() == twoGradeItem) { 
amountOfDisc = 4; 
tower.setAmountOfDisc(amountOfDisc); 
tower.putDiscOnTower(); 
t = 0; 
} else if (e.getSource() == threeGradeItem) { 
amountOfDisc = 5; 
tower.setAmountOfDisc(amountOfDisc); 
tower.putDiscOnTower(); 
t = 0; 
} else if (e.getSource() == renew) { 
tower.setAmountOfDisc(amountOfDisc); 
tower.putDiscOnTower(); 
t = 0; 
} else if (e.getSource() == autoButton) { 
tower.setAmountOfDisc(amountOfDisc); 
tower.putDiscOnTower(); 
int x = this.getBounds().x + this.getBounds().width; 
int y = this.getBounds().y; 
tower.getAutoMoveDisc().setLocation(x, y); 
tower.getAutoMoveDisc().setSize(280, this.getBounds().height); 
tower.getAutoMoveDisc().setVisible(true); } else if (e.getSource() == setDiscColor)// ������´���
{ 
SetDiscColorDlg colorDlg = new SetDiscColorDlg(this, tower); 
} else if (e.getSource() == setDiscWidth) { 
SetDiscWidthDlg widthDlg = new SetDiscWidthDlg(this, tower); 
t = 0; 
} else if (e.getSource() == setDiscAcount) { 
SetDiscAcountDlg acountDlg = new SetDiscAcountDlg(this, tower); 
amountOfDisc = tower.amountOfDisc; 
t = 0; } else if (e.getSource() == secondTime)// ��ʱ����
{ 
int hour, minute, second, a; 
String mytimer, strsec, strmin, strhour; 
t = t % (60 * 60 * 24); 
second = t % 60; 
a = t / 60; 
minute = a % 60; 
hour = a / 60; 
if (second <= 9) { 
strsec = "0" + String.valueOf(second); 
} else { 
strsec = String.valueOf(second); 
} 
if (minute <= 9) { 
strmin = "0" + String.valueOf(minute); 
} else { 
strmin = String.valueOf(minute); 
} 
if (hour <= 9) { 
strhour = "0" + String.valueOf(hour); 
} else { 
strhour = String.valueOf(hour); 
} 
mytimer = strhour + ":" + strmin + ":" + strsec; timetext.setText(" ��ʱ :" + mytimer); t = t + 1; 
} 
else if (e.getSource() == musicstart) { 
if (tag == false) { 
try { 
url = file.toURL(); 
clip = Applet.newAudioClip(url); 
} catch (Exception ex) { 
} 
clip.play(); 
tag = true; 
} 
} 
else if (e.getSource() == musicstop) { 
if (tag == true) { 
clip.stop(); 
tag = false; 
} 
} 
validate(); 
} 
public static void main(String args[]) { 
new HannoiWindow(); 
} 
} 