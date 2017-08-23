# Design
We have a mess, members who use mess, and one of the member is a
mess-manager. Each month we change mess-manager. PizzaSlice is used to
manage mess.

## Responsiblies of mess-manager
Mess-manager collects money from mess members and keep record of it.
Mess-manager have to record the the `expense` - money spent each day
and on which item. He also have to record daily details of member -
1. Has the member eaten Breakfast,Lunch, Dinner.
2. What type of food? - veg or non-veg.

Even if mess-manager record a particular `expense` how will he record
for which session (Breakfast, Lunch or Dinner) the expense was spend on?



## Design for command-line verison of PizzaSlice.

User will be presented with a menu of following format.
```
    Select one of the options:
    1. Change mess manager
    2. Expenses
    3. Daily Records
    4. List Daily Records
    5. List Record by Date
```

### Expenses
When user selects option `2.Expenses` he is presented with following
questions. 
```
    Select type of food (veg or non-veg):
```

User can just give `v` or `n` to mean `veg` or `non-veg` type.  If
mess-manager had to spend money on some item from mess-fund he would
have to record each entry in this table.  We are presented with some
questions here. Say if mess-manager spent his money on veg and non-veg
items does he have to record them individually?

Fields of `expense` table
```
    1. type - enum of three types - veg,non_veg.
    2. date - date money was spend.
    3. expense - amount spent.
    4. description - particulars about why money was spent.
``` 

I believe rest of the questions are easy implement and require no
further explanation.

## Daily records
Each day mess-manager have to record the details of each member for
sessions Breakfast, Lunch, Dinner. 

### How to we select members so we can assign them particular eating pattern?
We can list the members as a ordered list.(We are assuming the list of
members will be limited to say 20.  I am talking about a case where we
use the app to manage mess for members of flat-sharing setting.)   

1. We can use index (eg. `1`) to denote each user, put a space and then
eating pattern (`vvv`).

2. We can also use range-index `1-2`. In the future we can implement
bit of "learning" and group veg and non-veg members when listing them.

### How do we record the details eating pattern of a member?

One solution is to list the members as a ordered list with second
column recording his eating pattern. 

Eg.
```
    1. Tom   vvv
    2. Mike  vvv
    3. Peter vvv
```

Use `v` to signify veg food, use `n` to signify non-veg food. If
member eats misc items like egg - we can use use `e`. We are using
three characters to signify each session. So input `vvv` means veg
food for 3 times. `vvn` means veg food for breakfast,lunch and non-veg
for dinner. 

1. To record misc items like egg for a session we can use additon field
`e`. So input will be `vvve`.

2. Say manager want to record only for a particular session breakfast
of a member he can use `v__`.

3. Say he mistakenly enters dinner session for a member as non-veg and
current daily record of member is as `vvn`. He wants to change it to
`vvv`. He can just enter `vvv`.

4. We can use default values of `vvv` for all members.
5. If a user haven't eaten for a session, how do we record it? Say we
   want the clear dinner session for a user (note we are using default
   values), we can use `vv0`.
   
### Examples of daily reocord inputs
```
1 vvn
2-3 vnv
4 vvne
2 vv0  - to clear dinner session - he later find out that 2nd member hasn't eaten and manager has mistakely entered wrong value.
```

## How to calculate monthly expense for member?
If a member eat for a session we will be definitely charged for veg
food costs.  If a session qualifer a user is `n` it just means that he
as eaten non-veg in addition to veg food. We calculate 3 types of
expenses of a member monthly. 

1. veg-expense 
2. non-veg-expense.
3. misc expenese (like eating egg).

### Calculate veg-expense
We check the `expense` table to find the `net-veg-expenses` for a
month. Later we find the session-count of all members using
`daily_records` table as `net-session-count`. Find member's individual
session count as `session-count`.

``` 
member-monthly-veg-expense = (session-count/net-session-count) * (net-veg-expenses)
```

