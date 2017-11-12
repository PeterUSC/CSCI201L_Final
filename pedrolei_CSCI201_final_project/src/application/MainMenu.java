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
			
			//make the grid layout
			GridPane grid = new GridPane();
			grid.setAlignment(Pos.CENTER);
			grid.setHgap(10);
			grid.setVgap(10);
			grid.setPadding(new Insets(25, 25, 25, 25));

			Scene scene = new Scene(grid, 900, 825);
			
			final Text actiontarget = new Text();
	        grid.add(actiontarget, 1, 6);
	        actiontarget.setFill(Color.ANTIQUEWHITE);

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
			demo.setOnAction(new EventHandler<ActionEvent>() 
					{
						@Override
						public void handle(ActionEvent e)
						{
							try
							{
								c.createRequest("demo", "demo", 0);
							} 
							catch (ClassNotFoundException e1)
							{
								e1.printStackTrace();
							} 
							catch (IOException e1)
							{
								e1.printStackTrace();
							}
						}
					});
			//format demo button
			HBox hbBtnDemo = new HBox(10);
			hbBtnDemo.setAlignment(Pos.CENTER);
			hbBtnDemo.getChildren().add(demo);
			grid.add(hbBtnDemo, 1, 3);
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
							actiontarget.setText("BAD LOGIN");
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
							actiontarget.setText("Failed to Create New Account");
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
			grid.add(hbBtnAccount, 1, 4);
			
			
			scene.getStylesheets().add(getClass().getResource("MenuStyle.css").toExternalForm());
			primaryStage.setScene(scene);
			primaryStage.show();
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
