import javax.swing.*;
import java.awt.*;

public class Tela extends JFrame {
    private JPanel painel;
    //LISTA DE OPCOES
    private JComboBox jcbFonte, jcbTamanho, jcbCor;
    private JLabel jlFonte, jlTamanho, jlCor;
    //BOTOES
    private JButton jbAlterarFormatacao, jbLimparFormatacao, jbExcluirTexto;
    //RADIONBUTTON
    private JRadioButton jrbNegrito, jrbNormal, jrbItalico, jrbNegrito_Italico;
    private ButtonGroup bgEstilos;
    //CAIXA DE TEXTO
    private JTextArea jtxaTexto;
    private JScrollPane jspTexto;

    private String[] fontes = {"Arial", "Calibri", "Century Gothic", "Comic Sans MS", "Garamond", "Georgia", "Gill Sans MT", "Kalinga", "MingLiU_HKSCS", "Times New Roman"};
    private String[] tamanhos = {"8", "10", "12", "14", "16", "18", "20", "22", "24"};
    private String[] cores = {"Black", "Blue", "Cyan", "Green", "Magenta", "Orange", "Pink", "Red", "White", "Yellow"};

    public Tela(){
        painel = new JPanel();

        jcbFonte = new JComboBox(fontes);
        jcbTamanho = new JComboBox(tamanhos);
        jcbCor = new JComboBox(cores);
        jlFonte = new JLabel("Fonte: ");
        jlTamanho = new JLabel("Tamanho: ");
        jlCor = new JLabel("Cor: ");

        jbAlterarFormatacao = new JButton("Alterar formatação");
        jbLimparFormatacao = new JButton("Limpar formatacao");
        jbExcluirTexto = new JButton("Excluir texto");

        jrbNegrito = new JRadioButton("Negrito");
        jrbNormal = new JRadioButton("Normal");
        jrbItalico = new JRadioButton("Italico");
        jrbNegrito_Italico = new JRadioButton("Negrito-Italico");

        bgEstilos = new ButtonGroup();
        bgEstilos.add(jrbNegrito);
        bgEstilos.add(jrbNormal);
        bgEstilos.add(jrbItalico);
        bgEstilos.add(jrbNegrito_Italico);

        jtxaTexto = new JTextArea();
        jspTexto = new JScrollPane(jtxaTexto);
    }

    public void configurarJanela(){
        setVisible(true);
        setTitle("Lista 2");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(700, 600);
        setResizable(false);
        setLocation(200,50);
        add(painel);
        configurarPainel();
    }
    public void configurarPainel(){
        painel.setLayout(null);

        //FONTES
        jlFonte.setBounds(10, 10, 50, 20);
        painel.add(jlFonte);
        jcbFonte.setBounds(60, 10, 150, 20);
        painel.add(jcbFonte);
        //TAMANHOS
        jlTamanho.setBounds(250, 10, 80, 20);
        painel.add(jlTamanho);
        jcbTamanho.setBounds(310, 10, 100, 20);
        painel.add(jcbTamanho);
        //CORES
        jlCor.setBounds(470, 10, 30, 20);
        painel.add(jlCor);
        jcbCor.setBounds(500, 10, 150, 20);
        painel.add(jcbCor);
        //BOTOES
        AlterarFormatacao(); //altera para a formatação desejada
        jbAlterarFormatacao.setBounds(20, 50, 200, 30);
        painel.add(jbAlterarFormatacao);
        LimparFormatacao(); //Deixa a formatação padrão
        jbLimparFormatacao.setBounds(240, 50, 200, 30);
        painel.add(jbLimparFormatacao);
        ExcluirTexto(); //Limpa a caixa de texto
        jbExcluirTexto.setBounds(460, 50, 200, 30);
        jbExcluirTexto.setForeground(Color.RED);
        painel.add(jbExcluirTexto);
        //CAIXAS DE SELECAO
        jrbNegrito.setBounds(10, 90, 100, 20);
        painel.add(jrbNegrito);
        jrbNormal.setBounds(120, 90, 100, 20);
        painel.add(jrbNormal);
        jrbItalico.setBounds(240, 90, 100, 20);
        painel.add(jrbItalico);
        jrbNegrito_Italico.setBounds(360, 90, 250, 20);
        painel.add(jrbNegrito_Italico);
        //CAIXAS DE TEXTO
        jspTexto.setBounds(15, 120, 660, 430);
        jspTexto.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        jspTexto.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        jtxaTexto.setLineWrap(true);
        painel.add(jspTexto);

    }

    private void AlterarFormatacao(){
        jbAlterarFormatacao.addActionListener(evento ->{
            //FONTE, ESTILO E TAMANHO
            String Fonte = jcbFonte.getSelectedItem().toString();
            int TamanhoFonte = Integer.parseInt(jcbTamanho.getSelectedItem().toString());

            if(jrbNegrito.isSelected())
                jtxaTexto.setFont(new Font(Fonte, Font.BOLD, TamanhoFonte));
            else if (jrbItalico.isSelected())
                jtxaTexto.setFont(new Font(Fonte, Font.ITALIC, TamanhoFonte));
            else if (jrbNegrito_Italico.isSelected())
                jtxaTexto.setFont(new Font(Fonte, Font.ITALIC | Font.BOLD, TamanhoFonte));
            else
                jtxaTexto.setFont(new Font(Fonte, Font.PLAIN, TamanhoFonte));

            //COR
            String CorFonte = jcbCor.getSelectedItem().toString();
            Color color = Color.BLACK;
            switch (CorFonte){
                case "Black": color = Color.BLACK;
                    break;
                case "Blue": color = Color.BLUE;
                    break;
                case "Cyan": color = Color.CYAN;
                    break;
                case "Green": color = Color.GREEN;
                    break;
                case "Magenta": color = Color.MAGENTA;
                    break;
                case "Orange": color = Color.ORANGE;
                    break;
                case "Pink": color = Color.PINK;
                    break;
                case "Red": color = Color.RED;
                    break;
                case "White": color = Color.WHITE;
                    break;
                case "Yellow": color = Color.YELLOW;
                    break;
            }
            jtxaTexto.setForeground(color);
        });
    }

    private void LimparFormatacao(){
        jbLimparFormatacao.addActionListener(evento ->{
            jtxaTexto.setFont(new Font("Arial", Font.PLAIN, 12));
            jtxaTexto.setForeground(Color.BLACK);
        });
    }

    private void ExcluirTexto(){
        jbExcluirTexto.addActionListener(evento ->{
            jtxaTexto.setText("");
        });
    }

}


