import React from 'react';

const Part = ({ part }) => {
  return (
    <p>
      {part.name} {part.exercises}
    </p>
  );
};

const Content = ({ course }) => {
  return (
    <div>
      {course.parts.map((part) => (
        <Part key={part.id} part={part} />
      ))}
      <p>
        <strong>total of {course.parts.reduce((sum, part) => sum + part.exercises, 0)} exercises</strong>
      </p>
    </div>
  );
};

const Header = ({ course }) => {
  return <h1>{course.name}</h1>;
};

const Course = ({ course }) => {
  return (
    <div>
      <Header course={course} />
      <Content course={course} />
    </div>
  );
};

export default Course;
