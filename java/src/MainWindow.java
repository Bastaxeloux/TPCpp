import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.util.Arrays;

public class MainWindow extends JFrame {
    private static final long serialVersionUID = 1L;
    private JTextArea textArea;
    private JTextArea infoArea;
    private JTextField inputField;
    private JList<String> listBox;
    private DefaultListModel<String> listModel;
    private JComboBox<String> listTypeSelector;
    private Client client;

    public MainWindow() {

        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }

        setTitle("Lecteur Media - Maël Le Guillouzic");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(900, 600);
        setLocationRelativeTo(null);
        
        // ========== NOUVEAU LAYOUT POUR CENTRER ==========
        JPanel homePanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.insets = new Insets(10, 10, 10, 10); // Marge
        
        JLabel title = new JLabel("Lecteur Media", SwingConstants.CENTER);
        title.setFont(new Font("Serif", Font.BOLD, 32));
        homePanel.add(title, gbc);
    
        gbc.gridy++;
        JLabel subtitle = new JLabel("de Maël Le Guillouzic", SwingConstants.CENTER);
        subtitle.setFont(new Font("SansSerif", Font.ITALIC, 18));
        homePanel.add(subtitle, gbc);
    
        gbc.gridy++;
        JButton startButton = new JButton("Accéder au lecteur");
        startButton.setFont(new Font("SansSerif", Font.PLAIN, 18));
        startButton.addActionListener(e -> switchToMainPanel());
        homePanel.add(startButton, gbc);
    
        add(homePanel);
        setVisible(true);
    }
    

    // ========== PASSER À L'INTERFACE PRINCIPALE ==========
    private void switchToMainPanel() {
        getContentPane().removeAll();

        // Connexion au serveur
        try {
            client = new Client("localhost", 3331);
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Impossible de se connecter au serveur", "Erreur", JOptionPane.ERROR_MESSAGE);
            System.exit(1);
        }

        setLayout(new BorderLayout());

        // =================== BARRE D'OUTILS ===================
        JToolBar toolBar = new JToolBar();
        toolBar.add(createButton(new ServerAction("🔍 Média", "search_media "), "Rechercher un média"));
        toolBar.add(createButton(new ServerAction("🔍 Groupe", "search_group "), "Rechercher un groupe"));
        toolBar.add(createButton(new ServerAction("🔍 Partiel", "search_partial "), "Recherche partielle"));
        toolBar.add(createButton(new ServerAction("📜 Médias", "list_media"), "Lister tous les médias"));
        toolBar.add(createButton(new ServerAction("📂 Groupes", "list_groups"), "Lister tous les groupes"));
        add(toolBar, BorderLayout.NORTH);

        // =================== PANEL PRINCIPAL ===================
        JPanel mainPanel = new JPanel(new BorderLayout());
        add(mainPanel, BorderLayout.CENTER);

        // ========== PANNEAU DE RECHERCHE ==========
        JPanel searchPanel = new JPanel(new BorderLayout());
        inputField = new JTextField();
        JButton searchButton = new JButton("Rechercher");
        searchButton.addActionListener(new ServerAction("🔍", "search_media "));

        JButton playButton = new JButton("📺 Lire");
        playButton.addActionListener(e -> {
            String mediaName = inputField.getText().trim();
            if (!mediaName.isEmpty()) {
                new Thread(() -> client.send("play " + mediaName)).start();
            }
        });

        searchPanel.add(new JLabel("Rechercher : "), BorderLayout.WEST);
        searchPanel.add(inputField, BorderLayout.CENTER);
        searchPanel.add(searchButton, BorderLayout.EAST);
        searchPanel.add(playButton, BorderLayout.SOUTH);

        // ========== ZONE DE RÉSULTATS ==========
        textArea = new JTextArea(10, 40);
        textArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textArea);

        mainPanel.add(searchPanel, BorderLayout.NORTH);
        mainPanel.add(scrollPane, BorderLayout.CENTER);

        // ========== LISTE DES MÉDIAS / GROUPES ==========
        JPanel sidePanel = new JPanel(new BorderLayout());
        listTypeSelector = new JComboBox<>(new String[]{"📜 Médias", "📂 Groupes"});
        listTypeSelector.addActionListener(e -> refreshList());

        listModel = new DefaultListModel<>();
        listBox = new JList<>(listModel);
        listBox.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        listBox.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    String selected = listBox.getSelectedValue();
                    if (selected != null) {
                        if (listTypeSelector.getSelectedIndex() == 0) {
                            new Thread(() -> client.send("play " + selected)).start();
                        } else {
                            new Thread(() -> {
                                String response = client.send("search_group " + selected);
                                SwingUtilities.invokeLater(() -> {
                                    textArea.append("\n[Groupe : " + selected + "]\n" + response.replace("|", "\n") + "\n");
                                });
                            }).start();
                        }
                    }
                }
            }
        });

        JScrollPane listScrollPane = new JScrollPane(listBox);
        listScrollPane.setPreferredSize(new Dimension(250, 0));

        sidePanel.add(listTypeSelector, BorderLayout.NORTH);
        sidePanel.add(listScrollPane, BorderLayout.CENTER);
        add(sidePanel, BorderLayout.EAST);

        // ========== ZONE D'INFORMATION ==========
        infoArea = new JTextArea(5, 40);
        infoArea.setCaretPosition(0);
        infoArea.setEditable(false);
        infoArea.setText("Fonctionalitées :\n" +
                "- Vous pouvez voir a droite la liste des médias dans la database, ainsi que les groupes créés\n" +
                "- Une fois que vous voulez plus d'informations sur un groupe ou un média, tapez son nom dans la barre de recherche \n" +
                "- Il est alors possible de cliquer sur Play, rechercher (qui effectue une recherche partielle mais si il n'y a qu'un bout du nom du média) \n" +
                "- En théorie double cliquer sur un média a droite devrait l'ouvrir\n" +
                "- Les boutons en haut permettent d'afficher la liste des médias, des groupes, de rechercher un média ou un groupe\n" + 
                "Bugs connus :\n" +
                "- Parfois dans la zone de résultat un délai d'une action s'instaure. C'est a dire que si vous cliquer sur un bouton c'est le résultat du précédent clic qui s'affiche\n" +
                "- Souvent, la liste de droite affiche autre chose que la liste des médias et des groupes. Il faut alors cliquer plusieures fois sur le menu déroulant pour afficher correctement le contenu souhaité\n" +
                "- Parfois le double clic ne fonctionne pas a droite"
                );
        JScrollPane infoScrollPane = new JScrollPane(infoArea);
        add(infoScrollPane, BorderLayout.SOUTH);

        refreshList();
        revalidate();
        repaint();
    }

    // =================== ACTION SERVEUR ===================
    private class ServerAction extends AbstractAction {
        private String command;

        public ServerAction(String name, String cmd) {
            super(name);
            this.command = cmd;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            final String mediaName = inputField.getText().trim();
            final String request = command.equals("list_media") || command.equals("list_groups") ? command : command + mediaName;

            new Thread(() -> {
                String response = client.send(request);
                SwingUtilities.invokeLater(() -> {
                    if (command.startsWith("search_media") || command.startsWith("search_partial")) {
                        textArea.append("\n" + response.replace(";", "\n") + "\n");
                    } else if (command.equals("list_groups") || command.startsWith("search_group")) {
                        textArea.append("\n" + response.replace("|", "\n") + "\n");
                    } else {
                        textArea.append("\n" + response + "\n");
                    }
                    refreshList();
                });
            }).start();
        }
    }

    private void refreshList() {
        listModel.clear();
        new Thread(() -> {
            String response = client.send(listTypeSelector.getSelectedIndex() == 0 ? "list_media" : "list_groups");
            if (response != null) {
                String[] items = response.split(listTypeSelector.getSelectedIndex() == 0 ? ";" : "\\|");
                SwingUtilities.invokeLater(() -> {
                    listModel.clear();
                    Arrays.stream(items).forEach(listModel::addElement);
                });
            }
        }).start();
    }

    private JButton createButton(Action action, String tooltip) {
        JButton button = new JButton(action);
        button.setToolTipText(tooltip);
        return button;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(MainWindow::new);
    }
}
