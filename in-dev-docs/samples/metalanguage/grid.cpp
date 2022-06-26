#include <glm/glm.hpp>
#include "imgui/imgui.h"
class Grid
{
private:
    glm::vec3 position, row_vector, column_vector;
    int row_count, column_count;
    bool changed;

public:
    Grid()
    {
        this->changed = false;
    }

    void setPosition(glm::vec3 position)
    {
        this->position = position;
        this->changed = true;
    }

    void setRowVector(glm::vec3 row_vector)
    {
        this->row_vector = row_vector;
        this->changed = true;
    }

    void setColumnVector(glm::vec3 column_vector)
    {
        this->column_vector = column_vector;
        this->changed = true;
    }

    void setRowCount(int row_count)
    {
        this->row_count = row_count;
        this->changed = true;
    }

    void setColumnCount(int column_count)
    {
        this->column_count = column_count;
        this->changed = true;
    }

    glm::vec3 getPosition()
    {
        return this->position;
    }

    glm::vec3 getRowVector()
    {
        return this->row_vector;
    }

    glm::vec3 getColumnVector()
    {
        return this->column_vector;
    }

    int getRowCount()
    {
        return this->row_count;
    }

    int getColumnCount()
    {
        return this->column_count;
    }

    bool isChanged()
    {
        return this->changed;
    }
};

void log(Grid &grid)
{
    glm::vec3 position = grid.getPosition();
    ImGui::Text("position %f %f %f", position.x, position.y, position.z);
    ;
    glm::vec3 row_vector = grid.getRowVector();
    ImGui::Text("row_vector %f %f %f", row_vector.x, row_vector.y, row_vector.z);
    ;
    glm::vec3 column_vector = grid.getColumnVector();
    ImGui::Text("column_vector %f %f %f", column_vector.x, column_vector.y, column_vector.z);
    ;
    int row_count = grid.getRowCount();
    ImGui::Text("row_count %d", row_count);
    ;
    int column_count = grid.getColumnCount();
    ImGui::Text("column_count %d", column_count);
    ;
    bool changed = grid.isChanged();
    ImGui::Text("changed%d", grid.isChanged());
}
