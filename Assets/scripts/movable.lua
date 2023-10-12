function UpdateMove(deltaTime, speed)
	deltaVel = 0
	if input:TestInput(0) then
		deltaVel = deltaVel - speed
	end
	if input:TestInput(1) then
		deltaVel = deltaVel + speed
	end
	velX = deltaVel * deltaTime
	return velX
end
