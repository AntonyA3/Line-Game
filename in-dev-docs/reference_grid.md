# Reference Grid #
- The reference Grid will have it's own LineModel, However I would need to do Draw for every Grid and other object the has a lineModel  
- Another option is for another lineRepo to have a reference to the lineModel in grid, this would prevent having to iterate through each object that has a line model that should be drawn : 
- Another option is A grid will have a reference to object in line repo: If a grid
    -  Insert (Insert Grid into grid list), (Add new Line Model to lineRepo), getLastLineModel from line repo;
    - Delete (Find LineModel that matches Grid LineModel), (Delete The Line Model), (Delete The Grid) 

-Another Option is to just rename the class to refernce Grid by having a reference to a Grid and a LineModel: * Chosen Option *
    - Insert (Crete new Grid and add to Grid Repo) (Create New LineModel and add to repo), (Initialise Referece grid from the last Grid and the last LineModel)
    - Delete (Find Grid and delete) (Find LineModel and Delete) (Delete Reference Grid)

    