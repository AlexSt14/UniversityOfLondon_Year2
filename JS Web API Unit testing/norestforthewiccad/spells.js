const express = require('express');
const router = express.Router();

router.use(express.json());

let spells = 
   [
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

// get all spells
router.get('/', function(req, res){
    res.json(spells);
});
// get a specific spell
router.get('/:id', function(req, res){
   console.log("Request params: ", req.params);
   const spellId = parseInt(req.params.id,10);
   console.log("Received spellId: ", spellId);
   for(var i = 0; i < spells.length; i++) {
      if(spells[i].id == spellId) {
         console.log("The correct spell to return: ",spells[i]);
         res.json(spells[i]);
         return;
      }
   }
});
// update a specific spell
router.put('/:id', function(req, res){
   const spellId = parseInt(req.params.id,10);
   for(var i = 0; i < spells.length; i++) {
      if(spells[i].id == spellId) {
         spells[i].name = req.body.name;
         spells[i].ingredients = req.body.ingredients;
         spells[i].result = req.body.result;
         res.json(spells[i]);
         return;
      }
   }
});
// add a new spell
router.post('/', function(req, res){
   let spell = 
   {
      id:req.body.id, 
      name: req.body.name 
   };
   spells.push(spell);
   //console.log("The body of the request is ", req.body);
   //console.log("The full array of spells after adding the last spell is ", spells);
   res.json(spells);
});

module.exports = router;
