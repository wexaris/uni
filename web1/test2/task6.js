// 'Person' konstruktora funkcija
function Person(first, last, interests) {
    this.name = {'first' : first, 'last' : last};
    this.interests = interests;
    this.addInterest = function(interest) {
        this.interests.push(interest);
    }
}
var Bill = new Person('Bill', 'Smith', ['music', 'hockey']);
Person.prototype.course = 'Web technologies';
Bill.addInterest('books');

// Objektam 'Bill' būs šādi atribūti un motodes, jo tādus rada konstruktors 'Person':
// - atribūts objekts 'name':
//     - atribūts 'first': 'Bill'
//     - atribūts 'last': 'Smith'
// - atribūts masīvs 'interests': ['music', 'hockey']
// - metode 'addInterest(x)'

// Objektam 'Bill' būs šādi atribūti un motodes, jo prototips tiek modificēts:
// - atribūts 'course': 'Web technologies'

Person.prototype.printInfo = function(interest) {
    var str = this.name.first + " " + this.name.last + " has the following interests: ";
    str += this.interests.join(", ");
    return str;
}

var Jane = new Person('Jane', 'Smith', ['music', 'cooking']);
// your code to add a method printInfo
console.log(Jane.printInfo());
