const chai = require('chai');
const chaiHttp = require('chai-http');
const assert = require('assert');

chai.use(chaiHttp);

describe("Test top level / route", () => {
    it("It should have a 200 status code", (done) => {
        chai.request("http://localhost:3000")
        .get("/")
        .end( (err, res) => {
            assert.equal(res.status, 200);
            done();
        });
    });
    it("It should send the right message", (done) => {
        chai.request("http://localhost:3000")
        .get("/")
        .end((err,res) => {
            let data = JSON.parse(res.text);
            assert.equal(data.message, "Welcome to the norestforthewiccad API");
            done();
        });
    });
});

describe("Test the /spells route", () => {
    const expectedSpells = [
        {
            id: 1001, 
            name: "Rabbit foot positivity", 
            ingredients: [
               {name:"Foot of rabbit"}, 
               {name:"Juice of beetle"}], 
            result: "Good luck"
         },
         {
            id:1002,
            name: "Fox exeunta", 
            ingredients: [
               {name:"Foul of lion"}, 
               {name:"Spirit of hobo"}], 
            result: "Fox removed",
         }, 
         {
            id:1003, 
            name: "Hackus maximum", 
            ingredients: [
               {name:"Oxygenated hydrogen juice"}, 
               {name:"Effluent of bean"},
               {name:"Heat of joy"}], 
            result: "Fast coding"
         }
    ];
    it("It should have a 200 status code", (done) => {
        chai.request("http://localhost:3000")
        .get("/spells")
        .end((err, res) => {
            assert.equal(res.status, 200);
            done();
        });
    });
    it("It should output some data", (done) => {
        chai.request("http://localhost:3000")
        .get("/spells")
        .end((err,res) => {
            assert.deepEqual(res.body, expectedSpells);
            done();
        });
    });
    it("Testing the spell id", (done) => {
        chai.request("http://localhost:3000")
        .get("/spells/1002")
        .end((err,res) => {
            assert.deepEqual(res.body, expectedSpells[1]);
            done();
        });
    });
    it("Testing adding a new spell", (done) => {
        let spell = 
        {
            id:10010, 
            name: "Is this the right name for your spell and does it have any ingredients?", 
        };
        expectedSpells.push(spell);
        chai.request("http://localhost:3000")
        .post("/spells")
        .send(spell)
        .end((err,res) => {
            assert.deepEqual(res.body, expectedSpells);
            done();
        });
    });
    it("Testing the modifying of a spell", (done) => {
        let spell = 
        {
            id: 1001,
            name: "Updated Rabbit foot positivity",
            ingredients: [
                {name: "Foot of rabbit"},
                {name: "Joice of beetle"},
                {name: "Honey"}
            ],
            result: "Improved Rabbit foot"
        };
        expectedSpells[0] = spell;
        chai.request("http://localhost:3000")
        .put("/spells/1001")
        .send(spell)
        .end((err,res) => {
            assert.deepEqual(res.body, expectedSpells[0]);
            done();
        });
    });
});