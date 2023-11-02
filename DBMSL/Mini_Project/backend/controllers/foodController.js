const Food = require('../models/foodModel')
const mongoose = require('mongoose')

const getFoods = async (req, res) => {
    const foods = await Food.find({  }).sort({ createdAt: -1 })

    res.status(200).json(foods)
}

const getFood = async (req, res) => {
    const { id } = req.params

    if(!mongoose.Types.ObjectId.isValid(id)) {
        return res.status(404).json({error: 'No such food'})
    }

    const food = await Food.findById(id)

    if(!food) {
        return res.status(404).json({error: 'No such food'})
    }

    res.status(200).json(food)
}

const createFood = async (req, res) => {
    const {name, description, stars, price} = req.body

    let emptyFields = []

    if(!name) {
        emptyFields.push('name')
    }
    if(!description) {
        emptyFields.push('description')
    }
    if(!stars) {
        emptyFields.push('reps')
    }
    if(!price) {
        emptyFields.push('reps')
    }
    if(emptyFields.length > 0) {
        return res.status(400).json({ error: 'Please fill in all the fields', emptyFields })
    }

    try {
        const food = await Food.create({name, description, stars, price})
        res.status(200).json(food)
    } catch (error) {
        res.status(400).json({error: error.message})
    }
}

const deleteFood = async (req, res) => {
    const { id } = req.params

    if(!mongoose.Types.ObjectId.isValid(id)) {
        return res.status(404).json({error: 'No such workout'})
    }

    const food = await Food.findOneAndDelete({_id: id})

    if(!food) {
        return res.status(400).json({error: 'No such food'})
    }

    res.status(200).json(food)
}

const  updateFood = async (req, res) => {
    const { id } = req.params

    if(!mongoose.Types.ObjectId.isValid(id)) {
        return res.status(404).json({error: 'No such workout'})
    }

    const food = await Food.findOneAndUpdate({_id: id}, {
        ...req.body
    })

    if(!food) {
        return res.status(400).json({error: 'No such food'})
    }

    res.status(200).json(food)
}

module.exports = {
    getFood,
    getFoods,
    createFood,
    deleteFood,
    updateFood
}