package application;

import networking.*;
	
import java.io.IOException;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.stage.Stage;
import networking.Client;
import networking.ServerThread;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;


public class MainMenu extends Application 
{
	private Client c = createClient();
	@Override
	public void start(Stage primaryStage) 
	{
		try {
			
			//set menu name
			primaryStage.setTitle("Main Menu");
			Stage secondaryStage = new Stage();
			secondaryStage.setTitle("DEMO SCREEN");
			
			//make the gridPrimary layout for primary scene
			GridPane gridPrimary = new GridPane();
			gridPrimary.setAlignment(Pos.CENTER);
			gridPrimary.setHgap(10);
			gridPrimary.setVgap(10);
			gridPrimary.setPadding(new Insets(25, 25, 25, 25));

			Scene scenePrimary = new Scene(gridPrimary, 900, 675);
			
			final Text actiontarget = new Text();
	        gridPrimary.add(actiontarget, 1, 6);
	        actiontarget.setFill(Color.ANTIQUEWHITE);

			Label userNameLabel = new Label("User Name:");
			gridPrimary.add(userNameLabel, 0, 1);
			
			//Username input
			TextField userNameInput = new TextField();
			gridPrimary.add(userNameInput, 1, 1);

			Label pw = new Label("Password:");
			gridPrimary.add(pw, 0, 2);

			PasswordField pwBox = new PasswordField();
			gridPrimary.add(pwBox, 1, 2);
			
			//demo button
			Button demo = new Button("    Demo   ");
			demo.setOnAction(new EventHandler<ActionEvent>() 
					{
						@Override
						public void handle(ActionEvent e)
						{
							//play game
							
							primaryStage.hide();
							secondaryStage.show();
						}
					});
			//format demo button
			HBox hbBtnDemo = new HBox(10);
			hbBtnDemo.setAlignment(Pos.CENTER);
			hbBtnDemo.getChildren().add(demo);
			gridPrimary.add(hbBtnDemo, 1, 3);
			//login button
			Button login = new Button("   Login   ");
			login.setOnAction(new EventHandler<ActionEvent>() 
			{
				@Override
				public void handle(ActionEvent e)
				{
					try {
						boolean success = c.loginRequest(userNameInput.getText(), pwBox.getText());
						if(success == true) {
							int levelNumber = c.levelRequest(userNameInput.getText());
							actiontarget.setText("Login Accepted" + levelNumber);
						}else {
							actiontarget.setText("Invalid username or password");
						}
					} catch (ClassNotFoundException | IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
			//new account button
			Button newAccount = new Button("New Account");
			newAccount.setOnAction(new EventHandler<ActionEvent>() 
			{
				@Override
				public void handle(ActionEvent e)
				{
					try {
						boolean success = c.createRequest(userNameInput.getText(), pwBox.getText(), 0);
						if(success == true) {
							actiontarget.setText("Created New Account");
						}else {
							actiontarget.setText("Username already in use.");
						}
					} catch (ClassNotFoundException | IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
			//format login and account
			HBox hbBtnAccount = new HBox(10);
			hbBtnAccount.setAlignment(Pos.CENTER);
			hbBtnAccount.getChildren().add(login);
			hbBtnAccount.getChildren().add(newAccount);
			gridPrimary.add(hbBtnAccount, 1, 4);
			
			
			scenePrimary.getStylesheets().add(getClass().getResource("MenuStyle.css").toExternalForm());
			primaryStage.setScene(scenePrimary);
			primaryStage.show();
			
			
			/////////////////////////////////////////////
			////make the grid layout for secondary scene
			GridPane gridSecondary = new GridPane();
			gridSecondary.setAlignment(Pos.CENTER);
			gridSecondary.setHgap(10);
			gridSecondary.setVgap(10);
			gridSecondary.setPadding(new Insets(25, 25, 25, 25));
			
			Scene sceneSecondary = new Scene(gridSecondary, 900, 675);
			
			final Text actiontarget2 = new Text();
	        gridSecondary.add(actiontarget2, 1, 6);
	        actiontarget2.setFill(Color.ANTIQUEWHITE);

			
			Label userNameLabel2 = new Label("User Name:");
			
			//Username input
			TextField userNameInput2 = new TextField();

			Label pw2 = new Label("Password:");

			PasswordField pwBox2 = new PasswordField();

			gridSecondary.add(userNameLabel2, 0, 1);
			gridSecondary.add(userNameInput2, 1, 1);
			gridSecondary.add(pw2, 0, 2);
			gridSecondary.add(pwBox2, 1, 2);
			
			//returnMainMenu button
			Button returnMainMenu = new Button("Main Menu");
			returnMainMenu.setOnAction(new EventHandler<ActionEvent>() 
					{
						@Override
						public void handle(ActionEvent e)
						{
							//play game
							userNameInput.setText("");
							pwBox.setText("");
							secondaryStage.hide();
							primaryStage.show();	
						}
					});
			Button newAccount2 = new Button("New Account");
			newAccount2.setOnAction(new EventHandler<ActionEvent>() 
			{
				@Override
				public void handle(ActionEvent e)
				{
					try {
						boolean success = c.createRequest(userNameInput2.getText(), pwBox2.getText(), 1);
						if(success == true) {
							actiontarget2.setText("Created New Account");
						}else {
							actiontarget2.setText("Username already in use.");
						}
					} catch (ClassNotFoundException | IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
			//format demo button
			HBox hbBtnDemoScreen = new HBox(10);
			hbBtnDemoScreen.setAlignment(Pos.CENTER);
			hbBtnDemoScreen.getChildren().add(returnMainMenu);
			hbBtnDemoScreen.getChildren().add(newAccount2);
			gridSecondary.add(hbBtnDemoScreen, 1, 3);
			
			
			
			//login button
			
			
			
			sceneSecondary.getStylesheets().add(getClass().getResource("MenuStyle.css").toExternalForm());
			secondaryStage.setScene(sceneSecondary);
			
		} 
		catch(Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	private Client createClient() {
		return new Client();
	}
	
/*	public static void main(String[] args) 
	{
		launch(args);
	}*/
}
