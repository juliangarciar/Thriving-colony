#ifndef STATE_H
#define STATE_H

/**
 * @class State.
 * @brief Create a State type object.
 */
class State {

    public:
        /**
         * @brief Virtual method that will be implemented at classes that will inherit from State class.
         */
        virtual void Init() = 0;

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from State class.
         */
        virtual void Input() = 0;

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from State class.
         */
        virtual void Update() = 0;

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from State class.
         */
        virtual void Render() = 0;

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from State class.
         */
        virtual void CleanUp() = 0;
};

#endif

