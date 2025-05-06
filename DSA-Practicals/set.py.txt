class Set:
    """Implementation of a mathematical set using list storage"""
    
    def __init__(self, initial_element_count=0):
        """Initialize set and optionally add elements from user input"""
        self._elements = []
        
        for i in range(initial_element_count):
            element = int(input(f"Enter Element {i+1}: "))
            self.add(element)

    # ------------------------- Basic Operations -------------------------

    def get_elements(self):
        """Return the underlying elements list"""
        return self._elements
    
    def __str__(self):
        """String representation of the set"""
        elements_str = ", ".join(str(e) for e in self._elements)
        return f"{{ {elements_str} }}"
    
    def __len__(self):
        """Return number of elements in set"""
        return len(self._elements)
    
    def __contains__(self, element):
        """Check if element exists in set (using 'in' operator)"""
        return element in self._elements
    
    def is_empty(self):
        """Check if set contains no elements"""
        return len(self._elements) == 0
    
    def add(self, element):
        """Add unique element to the set"""
        if element not in self:
            self._elements.append(element)
    
    def remove(self, element):
        """Remove element from set if it exists"""
        if element in self._elements:
            self._elements.remove(element)

    # ------------------------- Set Comparisons -------------------------

    def __eq__(self, other_set):
        """Check if sets contain exactly the same elements"""
        if len(self) != len(other_set):
            return False
        return self.is_subset_of(other_set)
    
    def is_subset_of(self, other_set):
        """Check if all elements are contained in another set"""
        return all(element in other_set for element in self._elements)
    
    def is_proper_subset_of(self, other_set):
        """Check if strict subset relationship exists"""
        return (self.is_subset_of(other_set) and not (other_set.is_subset_of(self)))

    # ------------------------- Set Operations -------------------------

    def union(self, other_set):
        """Return new set containing all elements from both sets"""
        new_set = Set()
        new_set._elements = self._elements.copy()
        
        for element in other_set:
            if element not in new_set:
                new_set.add(element)
        return new_set
    
    def intersection(self, other_set):
        """Return new set containing common elements"""
        new_set = Set()
        
        for element in self._elements:
            if element in other_set:
                new_set.add(element)
        return new_set
    
    def difference(self, other_set):
        """Return new set with elements in this set but not in other set"""
        new_set = Set()
        
        for element in self._elements:
            if element not in other_set:
                new_set.add(element)
        return new_set

    # ------------------------- Iterator Support -------------------------

    def __iter__(self):
        """Enable iteration over the set"""
        return iter(self._elements)
    
    