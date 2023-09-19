import React, { useState } from 'react';
import Filter from './Filter';
import PersonForm from './PersonForm';
import Persons from './Persons';

const App = () => {
  const [persons, setPersons] = useState([
    { name: 'Arto Hellas', number: '040-123456', id: 1 },
    { name: 'Ada Lovelace', number: '39-44-5323523', id: 2 },
    { name: 'Dan Abramov', number: '12-43-234345', id: 3 },
    { name: 'Mary Poppendieck', number: '39-23-6423122', id: 4 },
  ]);
  const [newName, setNewName] = useState('');
  const [newNumber, setNewNumber] = useState('');
  const [searchTerm, setSearchTerm] = useState('');

  const submitHandler = (e) => {
    e.preventDefault(); // Prevent the default form submission
  
    // Check if the person already exists in the phonebook
    const personExists = persons.some((person) => person.name === newName);
  
    if (personExists) {
      alert(`${newName} is already added to the phonebook`);
    } else {
      // Create a new person object
      const newPerson = {
        name: newName,
        number: newNumber,
        id: persons.length + 1, // Generate a unique ID (you can use a more robust method)
      };
  
      // Update the persons state with the new person
      setPersons([...persons, newPerson]);
  
      // Clear the input fields
      setNewName('');
      setNewNumber('');
    }
  };
  
  const filteredPersons = persons.filter((person) =>
  person.name.toLowerCase().includes(searchTerm.toLowerCase())
  );



  return (
    <div>
      <h2>Phonebook</h2>

      <Filter searchTerm={searchTerm} setSearchTerm={setSearchTerm} />

      <h3>Add a new</h3>

      <PersonForm
        newName={newName}
        setNewName={setNewName}
        newNumber={newNumber}
        setNewNumber={setNewNumber}
        submitHandler={submitHandler}
      />

      <h3>Numbers</h3>

      <Persons persons={filteredPersons} />
    </div>
  )
};

export default App;
