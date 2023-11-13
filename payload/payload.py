class TodoItem:
    def __init__(self, task, completed=False):
        self.task = task
        self.completed = completed

class TodoList:
    def __init__(self):
        self.items = []

    def add_item(self, task):
        new_item = TodoItem(task)
        self.items.append(new_item)

    def remove_item(self, index):
        if 0 <= index < len(self.items):
            del self.items[index]
        else:
            print("Invalid index.")

    def mark_completed(self, index):
        if 0 <= index < len(self.items):
            self.items[index].completed = True
        else:
            print("Invalid index.")

    def display_list(self):
        print("Todo List:")
        for i, item in enumerate(self.items):
            status = "Done" if item.completed else "Not Done"
            print(f"{i + 1}. {item.task} - {status}")

def main():
    todo_list = TodoList()

    while True:
        print("\n1. Add Task")
        print("2. Remove Task")
        print("3. Mark Task as Completed")
        print("4. Display Todo List")
        print("5. Exit")

        choice = input("Enter your choice: ")

        if choice == "1":
            task = input("Enter the task: ")
            todo_list.add_item(task)
        elif choice == "2":
            index = int(input("Enter the index of the task to remove: ")) - 1
            todo_list.remove_item(index)
        elif choice == "3":
            index = int(input("Enter the index of the task to mark as completed: ")) - 1
            todo_list.mark_completed(index)
        elif choice == "4":
            todo_list.display_list()
        elif choice == "5":
            print("Exiting...")
            break
        else:
            print("Invalid choice. Try again.")

if __name__ == "__main__":
    main()
