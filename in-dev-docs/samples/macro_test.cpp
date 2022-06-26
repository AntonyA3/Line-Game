/*
Maybe Macro expansion may not be good enough


*/
#define TABLESIZE BUFFERSIZE
#define BUFFERSIZE 10

#define ENTITY(Name, Prop) \
    class Name{ Prop }; \
    void log(Name& Name) { \
        if(ImGui::TreeNode(Name)){ \
            Prop\
            \    
        }\
    }\

#define PROPERTY_LIST(properties...) \
    properties \

#define PROPERTY(type, name) type name;


ENTITY(Grid, PROPERTY_LIST(PROPERTY(int, position) PROPERTY(float, rotation)))

/*
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

/*


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


*/



int square(int num) {
    int z = TABLESIZE;
    return 1;
}




