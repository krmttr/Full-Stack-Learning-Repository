import React from 'react';

const Filter = ({ searchTerm, setSearchTerm }) => {
  return (
    <div>
      filter shown with{' '}
      <input
        type="text"
        value={searchTerm}
        onChange={(e) => setSearchTerm(e.target.value)}
      />
    </div>
  );
};

export default Filter;
