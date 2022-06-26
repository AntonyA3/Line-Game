
# Stage 1 : The Source File#


                <Entity name=Grid>
                    <Type id=glm::vec3>
                        <Property name=position  ops=[get, set]>
                        <Property name=row_vector ops=[get, set]>
                        <Property name=column_vector ops=[get, set]>
                    </Type>
                    <Type id=int>
                        <Property name=row_count ops=[get, set]>
                        <Property name=column_count ops=[get, set]>
                    </Type>
                    <Type id=bool>
                        <Property name=changed ops=[is]>
                    </Type>
                    <Cons>
                        this->changed = false; 
                    </Cons>
                    <AfterAnySet>
                        this->changed = true;
                    </AfterAnySet>
                    <Method rtntype=void scope=public name=reset>
                        this->changed = false;
                    </Method>
                </Entity>

# Stage 2.1 Convert to Dictionary
    grid = {
        "name": "Grid"
        "types:[
            {
                "id": "glm::vec3", 
                "properties":[
                    {"name": "position", "ops": ["get", "set"]},
                    {"name": "row_vector", "ops": ["get", "set"]},
                    {"name": "column_vector", "ops": [get, "set"]}
                ]
            },
            {
                "id : "int",
                "properties":[
                    {"name": "row_count", "ops": ["get", "set"]},
                    {"name": "column_count", "ops": ["get", "set"]}
                ]
            },
            {
                "id": "bool",
                "properties":[
                    {"name": "changed", "ops": ["is"]}
                ]
            }
        ],
        "cons": "this->changed = false;",
        "afterAnySet": "this->changed = true;" 
        "publicMethods": [
            {"rtntype": "void", "scope" : "public", "name": "reset"}
        ]
    }




# Stage N  The C++ code # 

void log(Grid& grid){
    if(ImGui::TreeNode("Grid")){
        glm::vec3 position = grid.getPosition();
        glm::vec3 row_vector = grid.getRowVector();
        glm::vec3 column_vector = grid.getColumnVector();
        int row_count = grid.getRowCount();
        int column_count = grid.getColumnCount();
        ImGui::Text("Position %f, %f, %f", position.x, position.y, position.z);
        ImGui::Text("Row Vector %f, %f, %f", row_vector.x, row_vector.y, row_vector.z);
        ImGui::Text("Column Vector %f, %f, %f", column_vector.x, column_vector.y, column_vector.z);
        ImGui::Text("Row Count %d", row_count);
        ImGui::Text("Column Count %d", column_count);
        ImGui::TreePop();
    }
}


class Grid
{
    bool changed;
    glm::vec3 position, row_vector, column_vector;
    int row_count, column_count;

    void onChanged(){
        this->changed = true;
    }

public:

    Grid(){
        this->changed = true;
    }

    void setPosition(glm::vec3 position){
        this->position = position;
        this->onChanged();
    }

    void setRowVector(glm::vec3 row_vector){
        this->row_vector = row_vector;
        this->onChanged();
    }

    void setColumnVector(glm::vec3 column_vector){
        this->column_vector = column_vector;
        this->onChanged();
    }

    void setRowCount(int row_count){
        this->row_count = row_count;
        this->onChanged();
    }

    void setColumnCount(int column_count){
        this->column_count = column_count;
        this->onChanged();
    }
    
    glm::vec3 getPosition(){
        return this->position;
    }

    glm::vec3 getRowVector(){
        return this->row_vector;
    }

    glm::vec3 getColumnVector(){
        return this->column_vector;
    }

    int getRowCount(){
        return this->row_count;    
    }

    int getColumnCount(){
        return this->column_count; 
    }
    
    void reset(){
        this->changed = false;
    }

    bool isChanged(){
        return this->changed;
    }
};