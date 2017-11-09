package application;
	
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;


public class Main extends Application {
	@Override
	public void start(Stage primaryStage) {
		try {
			
			//set menu name
			primaryStage.setTitle("Main Menu");
			
			//make the grid layout
			GridPane grid = new GridPane();
			grid.setAlignment(Pos.CENTER);
			grid.setHgap(10);
			grid.setVgap(10);
			grid.setPadding(new Insets(25, 25, 25, 25));

			Scene scene = new Scene(grid, 900, 825);
			
			

			Label userNameLabel = new Label("User Name:");
			grid.add(userNameLabel, 0, 1);
			
			//
			TextField userNameInput = new TextField();
			grid.add(userNameInput, 1, 1);

			Label pw = new Label("Password:");
			grid.add(pw, 0, 2);

			PasswordField pwBox = new PasswordField();
			grid.add(pwBox, 1, 2);
			
			//demo button
			Button demo = new Button("    Demo   ");
			//format demo button
			HBox hbBtnDemo = new HBox(10);
			hbBtnDemo.setAlignment(Pos.CENTER);
			hbBtnDemo.getChildren().add(demo);
			grid.add(hbBtnDemo, 1, 3);
			//login button
			Button login = new Button("   Login   ");
			//new account button
			Button newAccount = new Button("New Account");
			//format login and account
			HBox hbBtnAccount = new HBox(10);
			hbBtnAccount.setAlignment(Pos.CENTER);
			hbBtnAccount.getChildren().add(login);
			hbBtnAccount.getChildren().add(newAccount);
			grid.add(hbBtnAccount, 1, 4);
			
			
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			primaryStage.setScene(scene);
			primaryStage.show();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
