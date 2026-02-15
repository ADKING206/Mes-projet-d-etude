const UserList = [
    {name:"Jonh" , gender:"M", salary:"35000"},
    {name:"Jade" , gender:"F", salary:"42000"},
    {name:"Joe" , gender:"M", salary:"32000"},
    {name:"Jacky" , gender:"M", salary:"38000"},
]

const Augarray = UserList.filter(user =>user.gender=='M')
                        .map(user => user.salary+=1000)
                        .reduce((mensalarytotal,mensalary)=>mensalarytotal+mensalary);
console.log(Augarray);