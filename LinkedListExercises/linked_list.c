#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct list_node
{
    struct list_node *next; // Pointer to the next node
};

struct string_item
{
    struct list_node node;
    const char *string;
};

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));

    if (!item)
    {
        return NULL;
    }

    item->string = string;
    return item;
}

// Get the last node of the list
struct list_node *list_get_tail(struct list_node **head)
{
    struct list_node *current_node = *head;
    struct list_node *last_node = NULL;

    while (current_node)
    {
        last_node = current_node; // Last node updating
        current_node = current_node->next; // Go to the next node
    }

    return last_node;
}

// Add item at the end of the list
struct list_node *list_append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(head);

    if (!tail)
    {
        *head = item; // If the list is empty the item is the head of the list
    }
    else
    {
        tail->next = item; // Else the last item is the tail
    }

    item->next = NULL; // Set the next of the item NULL 
    return item;
}

// Remove an item at position
struct list_node *list_remove_at(struct list_node **head, int position)
{
    if (position < 0)
    {
        return NULL;
    }

    struct list_node *current_node = *head;
    struct list_node *prev_node = NULL;

    for (int i = 0; i < position && current_node; i++)
    {
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (!current_node)
    {
        return NULL;
    }

    if (prev_node)
    {
        prev_node->next = current_node->next;
    }
    else
    {
        *head = current_node->next;
    }

    current_node->next = NULL;
    return current_node;
}

void list_free(struct list_node **head)
{
    while (*head)
    {
        struct list_node *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main()
{
    struct string_item *my_linked_list = NULL;

    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("First"));
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Second"));
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Third"));
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Fourth"));

    struct list_node *removed_item = list_remove_at((struct list_node **)&my_linked_list, 1);

    if (removed_item)
    {
        free(removed_item);
    }

    struct string_item *string_item = my_linked_list;

    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }

    list_free((struct list_node **)&my_linked_list);

    return 0;
}