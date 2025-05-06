
class Person:
    def __init__(self,name,number):
        self.name = name
        self.number = number
        self.next = None
        
class TelephoneBookUsingChaining:
    def __init__(self,size):
        self.size  = size
        self.table = [None] * size

    def hashFunction(self,name):
        total = 0
        for char in name:
            total = total + ord(char)
        return total % self.size
    
    def checkEntryExists(self,current,name,number):
        while current is not None:
            if current.name == name and current.number == number:
                
                return True
            current = current.next
        return False
    
    def insert(self,name,number):
        newPerson = Person(name,number)
        index = self.hashFunction(name)

        if self.table[index] is None:
            self.table[index] = newPerson
            print(f"Inserted {name} at {index}th index with 0 comparisons")
            return
        
        present = self.checkEntryExists(self.table[index],name,number)
        if present:
            print(f"Entry already exists with details : \n Name : {name} \n Number : {number}")
            return
        
        current = self.table[index]
        comparisons = 1
        while current.next is not None:
            comparisons +=1
            current = current.next
        
        current.next = newPerson

        print(f"Inserted {name} at {index}th index with {comparisons} comparisons")

    def display(self):
        print("\nTelephone Book Records:")
        print("-----------------------")
        empty = True

        for index in range (self.size):
            
            current = self.table[index]

            while current is not None:
                empty = False
                print(f"Name: {current.name:<15} | Number: {current.number:<12} | Hash Index: {index}")
                current = current.next
        
        if empty:
            print("No records found in the telephone book")
        print("-----------------------\n")

    def delete_record(self, name):
        index = self.hashFunction(name)  # 1. Find which bucket to look in
        current = self.table[index]     # 2. Start at first person in bucket
        prev = None                     # 3. No previous person yet
        deleted = False                 # 4. Haven't deleted anything yet
        comparisons = 0                 # 5. Count how many checks we do

        while current is not None:       # 6. While we have people to check
            comparisons += 1
            if current.name == name:     # 7. Found our person!
                if prev is None:         # 8. Case 1: First in chain
                    self.table[index] = current.next
                else:                    # 9. Case 2: Middle/End of chain
                    prev.next = current.next
                deleted = True
                print(f"Deleted {name} after {comparisons} checks")
                break                   # 10. Exit the loop
        
            prev = current              # 11. Move to next person
            current = current.next

        if not deleted:                 # 12. If we didn't find them
            print(f"{name} not found after {comparisons} checks")
        return deleted                  # 13. Tell caller if we deleted someone     

    def search_record(self, name):
        """Search for a record by name in the telephone book"""
        index = self.hashFunction(name)  # 1. Calculate where the name should be
        current = self.table[index]     # 2. Get first entry at that index
        comparisons = 0                 # 3. Initialize comparison counter
        
        while current is not None:      # 4. Traverse through the chain
            comparisons += 1
            if current.name == name:    # 5. Found our record!
                print(f"Found {name}'s number: {current.number} (after {comparisons} comparisons)")
                return current.number  # 6. Return the phone number
            
            current = current.next     # 7. Move to next in chain
        
        # 8. If we get here, record wasn't found
        print(f"{name} not found (after {comparisons} comparisons)")
        return None

    def update_record(self, name, new_number):
        """Update a phone number for an existing name in the telephone book"""
        index = self.hashFunction(name)  # 1. Calculate where the name should be
        current = self.table[index]     # 2. Get first entry at that index
        comparisons = 0                 # 3. Initialize comparison counter
        updated = False                 # 4. Track if update was successful
        
        while current is not None:      # 5. Traverse through the chain
            comparisons += 1
            if current.name == name:    # 6. Found our record!
                current.number = new_number  # 7. Update the phone number
                updated = True
                print(f"Updated {name}'s number to {new_number} (after {comparisons} comparisons)")
                break
            
            current = current.next     # 8. Move to next in chain
        
        if not updated:                # 9. If we didn't find the record
            print(f"Cannot update - {name} not found (after {comparisons} comparisons)")
        return updated                # 10. Return status        

class TelephoneBookUsingLinearProbing:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size  # Each slot will store a tuple (name, number) or None
    
    def hashFunction(self, name):
        return sum(ord(char) for char in name) % self.size
    
    def insert(self, name, number):
        index = self.hashFunction(name)
        comparisons = 0
        original_index = index
        
        while True:
            comparisons += 1
            # Case 1: Found empty slot
            if self.table[index] is None:
                self.table[index] = (name, number)
                print(f"Inserted {name} at index {index} (after {comparisons} comparisons)")
                return True
            
            # Case 2: Found existing entry with same name and number
            if self.table[index][0] == name and self.table[index][1] == number:
                print(f"Entry exists: {name} - {number} (after {comparisons} comparisons)")
                return False
            
            # Case 3: Slot occupied by different entry, probe next
            index = (index + 1) % self.size
            
            # Prevent infinite loop if table is full
            if index == original_index:
                print("Table is full, cannot insert")
                return False

    def display_records(self):
        print("\nTelephone Book Records (Linear Probing):")
        print("-------------------------------------")
        empty = True
        
        for index in range(self.size):
            entry = self.table[index]
            if entry is not None:
                empty = False
                name, number = entry
                print(f"Name: {name:<15} | Number: {number:<12} | Index: {index}")
        
        if empty:
            print("No records found in the telephone book")
        print("-------------------------------------\n")

    def search_record(self, name):
        index = self.hashFunction(name)
        comparisons = 0
        original_index = index
        
        while True:
            comparisons += 1
            # Case 1: Found our record
            if self.table[index] is not None and self.table[index][0] == name:
                number = self.table[index][1]
                print(f"Found {name}'s number: {number} (after {comparisons} comparisons)")
                return number
            
            # Case 2: Found empty slot - means not in table
            if self.table[index] is None:
                print(f"{name} not found (after {comparisons} comparisons)")
                return None
            
            # Case 3: Continue probing
            index = (index + 1) % self.size
            
            # Prevent infinite loop
            if index == original_index:
                print(f"{name} not found (after {comparisons} comparisons)")
                return None

    def delete_record(self, name):
        index = self.hashFunction(name)
        comparisons = 0
        original_index = index
        
        while True:
            comparisons += 1
            # Case 1: Found our record
            if self.table[index] is not None and self.table[index][0] == name:
                self.table[index] = None  # Simply mark as None
                print(f"Deleted {name} (after {comparisons} comparisons)")
                return True
            
            # Case 2: Found empty slot - means not in table
            if self.table[index] is None:
                print(f"{name} not found (after {comparisons} comparisons)")
                return False
            
            # Case 3: Continue probing
            index = (index + 1) % self.size
            
            # Prevent infinite loop
            if index == original_index:
                print(f"{name} not found (after {comparisons} comparisons)")
                return False

    def update_record(self, name, new_number):
        index = self.hashFunction(name)
        comparisons = 0
        original_index = index
        
        while True:
            comparisons += 1
            # Case 1: Found our record
            if self.table[index] is not None and self.table[index][0] == name:
                self.table[index] = (name, new_number)  # Update the tuple
                print(f"Updated {name}'s number to {new_number} (after {comparisons} comparisons)")
                return True
            
            # Case 2: Found empty slot - means not in table
            if self.table[index] is None:
                print(f"Cannot update - {name} not found (after {comparisons} comparisons)")
                return False
            
            # Case 3: Continue probing
            index = (index + 1) % self.size
            
            # Prevent infinite loop
            if index == original_index:
                print(f"Cannot update - {name} not found (after {comparisons} comparisons)")
                return False
            


            
t = TelephoneBookUsingChaining(10)

t.insert("Alice",21454)
t.insert("fasda",5445484)
t.insert("Alice",21454)
t.insert("Alice",565496544)
t.display()

            
            
            
        
            


    
    
